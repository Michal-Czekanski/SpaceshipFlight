#include "../headers/RenderableObject.h"

RenderableObject::RenderableObject(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, 
	glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace): CameraAttachable(position, rotationQuat, vectorForward, vectorTop)
{
	this->model = model;
	this->topInModelSpace = topInModelSpace;
	this->forwardInModelSpace = forwardInModelSpace;

	this->modelMatrix = glm::translate(position) * glm::mat4_cast(rotationQuat);
}

glm::mat4 RenderableObject::getModelMatrix()
{
	return this->modelMatrix;
}

obj::Model RenderableObject::getModel()
{
	return this->model;
}
