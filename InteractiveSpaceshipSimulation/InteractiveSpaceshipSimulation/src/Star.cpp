#include "../headers/Star.h"

Star::Star(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, 
	obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, glm::vec3 scale,
	glm::vec3 lightColor, float lightStrength):
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
{
	this->lightColor = lightColor;
	this->lightStrength = lightStrength;
}

glm::vec3 Star::getLightColor()
{
	return this->lightColor;
}

float Star::getLightStrength()
{
	return this->lightStrength;
}

