#pragma once

#include "../utils/objload.h"
#include "glm.hpp"
#include "ext.hpp"

class ModelData
{
private:
	const obj::Model model;
	const obj::Model simplifiedModel;
	const glm::vec3 forward;
	const glm::vec3 top;

public:
	ModelData(obj::Model &model, glm::vec3 modelForward, glm::vec3 modelTop);

	ModelData(obj::Model& model, obj::Model& simplifiedModel, glm::vec3 modelForward, glm::vec3 modelTop);


	const obj::Model& getModel();
	const obj::Model& getSimplifiedModel();

	const glm::vec3& getForward();
	const glm::vec3& getTop();
};

