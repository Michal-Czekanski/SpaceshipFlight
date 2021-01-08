#include "../headers/AttachableCamera.h"

glm::vec3 AttachableCamera::calculateCamOffset()
{
	glm::vec3 camOffset = this->attachedObject->getVectorForward() * this->camOffsetMultiplier;
	camOffset -= this->attachedObject->getVectorTop() * this->upOffsetMultiplier;
	return camOffset;
}

AttachableCamera::AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier)
{
	this->camOffsetMultiplier = camOffsetMultiplier;
	this->upOffsetMultiplier = upOffsetMultiplier;
}

AttachableCamera::AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier, ICameraAttachable* attachedObject)
{
	this->camOffsetMultiplier = camOffsetMultiplier;
	this->upOffsetMultiplier = upOffsetMultiplier;
	this->attachedObject = attachedObject;

	this->initCameraRotation = rotateV1ToV2(this->initCameraLookDir, attachedObject->getVectorForward());
}

glm::mat4 AttachableCamera::updateCameraMatrix()
{
	glm::vec3 camPos = this->attachedObject->getPosition() - this->calculateCamOffset();
	this->cameraMatrix = Core::createViewMatrixQuat(camPos, this->initCameraRotation * glm::inverse(this->attachedObject->getRotationQuat()));
	return this->cameraMatrix;
}

glm::mat4 AttachableCamera::getCameraMatrix()
{
	return this->cameraMatrix;
}

