#include "../headers/RenderableObject.h"

RenderableObject::RenderableObject(glm::vec3 position, ModelData &modelData, glm::vec3 scale, GLuint programDraw):
	ObjectInSpace(position, modelData.getForward(), modelData.getTop()), texture(0)
{
	this->positionMat = glm::translate(position);

	this->rotationMat = glm::mat4_cast(rotationQuat);
	
	this->scale = scale;
	this->scaleMat = glm::scale(scale);

	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;

	this->model = modelData.getModel();
	this->renderContext.initFromOBJ(this->model);

	this->programDraw = programDraw;

	this->simplifiedModel = modelData.getSimplifiedModel();
	this->simplifiedRenderContext.initFromOBJ(this->simplifiedModel);
}

glm::mat4 RenderableObject::getModelMatrix()
{
	return this->modelMatrix;
}

obj::Model RenderableObject::getModel()
{
	return this->model;
}

void RenderableObject::update()
{
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}

glm::vec3 RenderableObject::getScale()
{
	return this->scale;
}

void RenderableObject::rotate(glm::quat rotation)
{
	this->rotationQuat = rotation;
	this->rotationMat = glm::mat4_cast(this->rotationQuat);
	updateDirections(rotation);
}

glm::vec3 RenderableObject::getColor()
{
	return this->color;
}

void RenderableObject::setColor(glm::vec3 color)
{
	this->color = color;
}

Core::RenderContext RenderableObject::getRenderContext()
{
	return this->renderContext;
}

Core::RenderContext RenderableObject::getSimplifiedRenderContext()
{
	return simplifiedRenderContext;
}

void RenderableObject::setTexture(GLuint texture)
{
	this->texture = texture;
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
	Core::RenderContext chosenContext = dlod.whichContextUse(distFromCam, simplifiedRenderContext, renderContext);
	Core::DrawContext(chosenContext);
	glUseProgram(0);
}
