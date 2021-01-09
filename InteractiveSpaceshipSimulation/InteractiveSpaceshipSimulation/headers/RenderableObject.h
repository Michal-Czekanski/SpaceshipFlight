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

	glm::vec3 scale;
public:
	RenderableObject(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale);

	glm::mat4 getModelMatrix();

	obj::Model getModel();

	/// <summary>
	/// Update is called on every frame.
	/// </summary>
	virtual void update() {};
};

