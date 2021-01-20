#pragma once

#include "../utils/objload.h"
#include "glm.hpp"
#include "ext.hpp"

class ModelData
{
private:
	obj::Model model;
	obj::Model simplifiedModel;
	glm::vec3 forward;
	glm::vec3 top;

public:
	ModelData(obj::Model &model, glm::vec3 modelForward, glm::vec3 modelTop);

	ModelData(obj::Model& model, obj::Model& simplifiedModel, glm::vec3 modelForward, glm::vec3 modelTop);


	obj::Model getModel();
	obj::Model getSimplifiedModel();

	glm::vec3 getForward();
	glm::vec3 getTop();
};

