#include "../headers/Star.h"



Star::Star(glm::vec3 position, ModelData &modelData, 
	glm::vec3 scale, glm::vec3 lightColor, float lightStrength):
	RenderableObject(position, modelData, scale)
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

