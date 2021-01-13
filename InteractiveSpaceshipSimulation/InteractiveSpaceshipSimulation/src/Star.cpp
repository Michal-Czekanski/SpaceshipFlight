#include "../headers/Star.h"



Star::Star(glm::vec3 position, ModelData& modelData, glm::vec3 scale, StarLight* light, GLuint programDraw):
	RenderableObject(position, modelData, scale, programDraw)
{
	this->light = light;
	this->light->update(position);
}

StarLight* Star::getLight()
{
	return this->light;
}

void Star::draw(GLuint program, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos, std::vector<StarLight*>& starsLights)
{
	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "starPos"), position.x, position.y, position.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(&model);

	glUseProgram(0);
}

