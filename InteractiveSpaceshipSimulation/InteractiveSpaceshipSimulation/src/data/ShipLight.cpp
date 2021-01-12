#include "../../headers/data/ShipLight.h"

ShipLight::ShipLight(float lightConeHeight, float lightConeBaseRadius, glm::vec3 position, glm::vec3 lightDirection)
{
	this->lightConeHeight = lightConeHeight;
	this->lightConeBaseRadius = lightConeBaseRadius;
	this->position = position;
	this->lightDirection = lightDirection;
}

void ShipLight::update(glm::vec3 position, glm::vec3 lightDirection)
{
	this->position = position;
	this->lightDirection = lightDirection;
}
