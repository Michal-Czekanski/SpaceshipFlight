#include "../headers/Star.h"



Star::Star(glm::vec3 position, ModelData& modelData, glm::vec3 scale, StarLight* light):
	RenderableObject(position, modelData, scale)
{
	this->light = light;
	this->light->update(position);
}

StarLight* Star::getLight()
{
	return this->light;
}

