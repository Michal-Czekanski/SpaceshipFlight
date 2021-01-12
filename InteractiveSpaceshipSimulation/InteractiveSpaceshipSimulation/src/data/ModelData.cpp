#include "../../headers/data/ModelData.h"

ModelData::ModelData(obj::Model& model, glm::vec3 modelForward, glm::vec3 modelTop)
{
	this->model = model;
	this->forward = modelForward;
	this->top = modelTop;
}

obj::Model ModelData::getModel()
{
	return this->model;
}

glm::vec3 ModelData::getForward()
{
	return this->forward;
}

glm::vec3 ModelData::getTop()
{
	return this->top;
}
