#include "objectsInSpace/renderables/Star.h"



Star::Star(glm::vec3 position, const RenderData& renderData, glm::vec3 scale, StarLight* light, GLuint programDraw, TextureData textureData):
	RenderableObject(position, renderData, scale, programDraw, textureData)
{
	this->light = light;
	this->light->update(position);
	rigidActor = RigidbodyFactory::createPlanetMoonStarRigidbody(position, rotationQuat, this);
}

StarLight* Star::getLight()
{
	return this->light;
}

void Star::draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos, std::vector<StarLight*>& starsLights)
{
	glUseProgram(programDraw);

	glUniform3f(glGetUniformLocation(programDraw, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(programDraw, "starPos"), position.x, position.y, position.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(programDraw, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(programDraw, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);


	if (textureData.getTexture() != 0)
	{
		Core::SetActiveTexture(textureData.getTexture(), "textureSampler", programDraw, 0);

	}
	Core::RenderContext renderContext = renderData.getRenderContext();
	Core::DrawContext(renderContext);

	

	glUseProgram(0);
}

