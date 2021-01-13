#include "../../headers/data/StarLight.h"

StarLight::StarLight(glm::vec3 color, float strength)
{
	this->color = color;
	this->strength = strength;
}

float StarLight::getStrength()
{
	return this->strength;
}

glm::vec3 StarLight::getColor()
{
	return this->color;
}

glm::vec3 StarLight::getPosition()
{
	return this->position;
}
