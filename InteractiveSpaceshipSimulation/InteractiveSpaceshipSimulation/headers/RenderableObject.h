#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "CameraAttachable.h"

class RenderableObject: public CameraAttachable 
{
protected:
	glm::mat4 modelMatrix;
	obj::Model model;

	glm::vec3 topInModelSpace;
	glm::vec3 forwardInModelSpace;
public:
	RenderableObject(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace);
};

