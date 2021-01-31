#include "../../headers/data/ModelData.h"

ModelData::ModelData(obj::Model& model, glm::vec3 modelForward, glm::vec3 modelTop):
	model(model), forward(modelForward), top(modelTop), simplifiedModel(model)
{
}

ModelData::ModelData(obj::Model& model, obj::Model& simplifiedModel, glm::vec3 modelForward, glm::vec3 modelTop):
	model(model), forward(modelForward), top(modelTop), simplifiedModel(simplifiedModel)
{
}

const obj::Model& ModelData::getModel() const
{
	return model;
}

const obj::Model& ModelData::getSimplifiedModel() const
{
	return simplifiedModel;
}

const glm::vec3& ModelData::getForward() const
{
	return forward;
}

const glm::vec3& ModelData::getTop() const
{
	return top;
}
