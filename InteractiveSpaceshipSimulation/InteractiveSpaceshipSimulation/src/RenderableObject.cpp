#include "../headers/RenderableObject.h"

RenderableObject::RenderableObject(glm::vec3 position, ModelData &modelData, glm::vec3 scale):
	ObjectInSpace(position, modelData.getForward(), modelData.getTop())
{
	this->positionMat = glm::translate(position);

	this->rotationMat = glm::mat4_cast(rotationQuat);
	
	this->scale = scale;
	this->scaleMat = glm::scale(scale);

	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;

	this->model = modelData.getModel();
}

glm::mat4 RenderableObject::getModelMatrix()
{
	return this->modelMatrix;
}

obj::Model RenderableObject::getModel()
{
	return this->model;
}

void RenderableObject::update()
{
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}

glm::vec3 RenderableObject::getScale()
{
	return this->scale;
}

void RenderableObject::rotate(glm::quat rotation)
{
	this->rotationQuat = rotation;
	this->rotationMat = glm::mat4_cast(this->rotationQuat);
	updateDirections(rotation);
}
