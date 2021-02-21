#include "objectsInSpace/renderables/RenderableObject.h"

RenderableObject::RenderableObject(glm::vec3 position, const RenderData& renderData, glm::vec3 scale, GLuint programDraw,
	TextureData textureData):
	renderData(renderData), textureData(textureData),
	ObjectInSpace(position, renderData.getModelData().getForward(), renderData.getModelData().getTop())
{
	this->positionMat = glm::translate(position);

	this->rotationMat = glm::mat4_cast(rotationQuat);
	
	this->scale = scale;
	this->scaleMat = glm::scale(scale);

	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;

	this->programDraw = programDraw;
}

glm::mat4 RenderableObject::getModelMatrix()
{
	return this->modelMatrix;
}

void RenderableObject::physicsUpdate(RenderableUpdateData& update)
{
	this->rotationQuat = update.getRotation();
	updateDirections(rotationQuat);

	position = update.getPosition();
	positionMat = glm::translate(position);
	modelMatrix = update.getModelMatrix() * scaleMat;
}

glm::vec3 RenderableObject::getScale()
{
	return this->scale;
}

void RenderableObject::rotate(glm::quat rotation)
{
	if (rigidActor)
	{
		rigidActor->setGlobalPose(PxTransform(rigidActor->getGlobalPose().p, PhysxGLMConverter::quatToPxQuat(rotation)));
	}
}

glm::vec3 RenderableObject::getColor()
{
	return this->color;
}

void RenderableObject::setColor(glm::vec3 color)
{
	this->color = color;
}

void RenderableObject::draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
	std::vector<StarLight*> &starsLights)
{
	glUseProgram(programDraw);

	glm::mat4 modelMatrix = this->getModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(programDraw, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	glm::mat4 modelViewProjectionMatrix = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(programDraw, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&modelViewProjectionMatrix);
	glm::vec3 shipPosition = shipLight.getPosition();
	glUniform3f(glGetUniformLocation(programDraw, "shipPos"), shipPosition.x, shipPosition.y, shipPosition.z);
	glm::vec3 shipDirection = shipLight.getLightDirection();
	glUniform3f(glGetUniformLocation(programDraw, "shipDirection"), shipDirection.x, shipDirection.y, shipDirection.z);

	glUniform1f(glGetUniformLocation(programDraw, "shipLightConeHeight"), shipLight.getLightConeHeight());
	glUniform1f(glGetUniformLocation(programDraw, "shipLightConeRadius"), shipLight.getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(programDraw, "shipLightColor"),
		shipLight.getLightColor().x, shipLight.getLightColor().y, shipLight.getLightColor().z);

	glUniform3f(glGetUniformLocation(programDraw, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(programDraw, "cameraPos"), camPos.x, camPos.y, camPos.z);


	std::vector<glm::vec3> starsPos;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsPos.push_back(starsLights[i]->getPosition());
	}
	glUniform3fv(glGetUniformLocation(programDraw, "starsPos"), starsLights.size(), reinterpret_cast<GLfloat*>(starsPos.data()));

	std::vector<float> starsLightStr;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsLightStr.push_back(starsLights[i]->getStrength());
	}
	glUniform1fv(glGetUniformLocation(programDraw, "starsLightStr"), starsLights.size(), reinterpret_cast<GLfloat*>(starsLightStr.data()));

	std::vector<glm::vec3> starsLightCol;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsLightCol.push_back(starsLights[i]->getColor());
	}
	glUniform3fv(glGetUniformLocation(programDraw, "starsLightCol"), starsLights.size(), reinterpret_cast<GLfloat*>(starsLightCol.data()));

	DiscreteLOD dlod = DiscreteLOD();
	float distFromCam = glm::distance(position, camPos);
	Core::RenderContext chosenContext = dlod.whichContextUse(distFromCam, &renderData);

	if (textureData.getTexture() != 0)
		Core::SetActiveTexture(textureData.getTexture(), "textureSampler", programDraw, 0);
	if (textureData.getTextureNormal() != 0)
		Core::SetActiveTexture(textureData.getTextureNormal(), "normalSampler", programDraw, 1);

	Core::DrawContext(chosenContext);
	glUseProgram(0);
}
