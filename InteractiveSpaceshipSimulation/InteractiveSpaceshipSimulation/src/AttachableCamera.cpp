#include "../headers/AttachableCamera.h"

AttachableCamera::AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier)
{
	this->camOffsetMultiplier = camOffsetMultiplier;
	this->upOffsetMultiplier = upOffsetMultiplier;
	this->camPos = glm::vec3(0, 0, 0);
	this->attachedObject = NULL;
}

AttachableCamera::AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier, ObjectInSpace* attachedObject)
{
	this->camOffsetMultiplier = camOffsetMultiplier;
	this->upOffsetMultiplier = upOffsetMultiplier;
	this->attachedObject = attachedObject;

	this->initCameraRotation = rotateV1ToV2(this->initCameraLookDir, attachedObject->getVectorForward());
	updateCameraMatrix();
}

glm::vec3 AttachableCamera::calculateCamOffset()
{
	glm::vec3 camOffset = this->attachedObject->getVectorForward() * this->camOffsetMultiplier;
	camOffset -= this->attachedObject->getVectorTop() * this->upOffsetMultiplier;
	return camOffset;
}

glm::mat4 AttachableCamera::updateCameraMatrix()
{
	this->camPos = this->attachedObject->getPosition() - this->calculateCamOffset();
	this->cameraMatrix = Core::createViewMatrixQuat(this->camPos, this->initCameraRotation * glm::inverse(this->attachedObject->getRotationQuat()));
	return this->cameraMatrix;
}

glm::mat4 AttachableCamera::getCameraMatrix()
{
	return this->cameraMatrix;
}

glm::vec3 AttachableCamera::getCamPos()
{
	return this->camPos;
}

