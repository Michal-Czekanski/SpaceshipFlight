#include "../../headers/data/ShipLight.h"

ShipLight::ShipLight(float lightConeHeight, float lightConeBaseRadius, glm::vec3 position, glm::vec3 lightDirection, glm::vec3 lightColor)
{
	this->lightConeHeight = lightConeHeight;
	this->lightConeBaseRadius = lightConeBaseRadius;
	this->position = position;
	this->lightDirection = lightDirection;
	this->lightColor = lightColor;
}

void ShipLight::update(glm::vec3 position, glm::vec3 lightDirection)
{
	this->position = position;
	this->lightDirection = lightDirection;
}

float ShipLight::getLightConeHeight()
{
	return this->lightConeHeight;
}

float ShipLight::getLightConeBaseRadius()
{
	return this->lightConeBaseRadius;
}

glm::vec3 ShipLight::getPosition()
{
	return this->position;
}

glm::vec3 ShipLight::getLightDirection()
{
	return this->lightDirection;
}
