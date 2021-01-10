#include "../headers/Ship.h"

Ship::Ship(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop,
	float shipSpeed, float rotationSpeed,
	obj::Model shipModel, glm::quat rotationQuat,
	glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace, glm::vec3 scale,
	float lightConeHeight, float lightConeRadius):
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, shipModel, shipTopInModelSpace, shipDirectionInModelSpace, scale)
{
	this->speed = shipSpeed;
	this->rotationSpeed = rotationSpeed;

	this->lightConeHeight = lightConeHeight;
	this->lightConeBaseRadius = lightConeRadius;
}

void Ship::moveForward()
{
	this->position += vectorForward * speed * Time::getDeltaTimeSec();
	this->updateModelMatrix();
}

void Ship::moveBackwards()
{
	this->position -= vectorForward * speed * Time::getDeltaTimeSec();
	this->updateModelMatrix();
}

void Ship::rotateShip(bool pitchUp, bool pitchDown, bool yawRight, bool yawLeft, bool rollRigt, bool rollLeft)
{
	float rotationAngleX = 0.0f; float rotationAngleY = 0.0f; float rotationAngleZ = 0.0f;
	if (pitchUp) { rotationAngleX += rotationSpeed * Time::getDeltaTimeSec(); };
	if (pitchDown) { rotationAngleX -= rotationSpeed * Time::getDeltaTimeSec(); };

	if (yawRight) { rotationAngleY -= rotationSpeed * Time::getDeltaTimeSec(); };
	if (yawLeft) { rotationAngleY += rotationSpeed * Time::getDeltaTimeSec(); };

	if (rollRigt) { rotationAngleZ += rotationSpeed * Time::getDeltaTimeSec(); };
	if (rollLeft) { rotationAngleZ -= rotationSpeed * Time::getDeltaTimeSec(); };


	this->rotationQuat = calculateRotationQuatLocalAxises(this->rotationQuat, this->vectorRight, this->vectorTop, this->vectorForward, rotationAngleX, rotationAngleY, rotationAngleZ);
	this->rotationMat = glm::mat4_cast(this->rotationQuat);

	this->vectorForward = glm::normalize(this->rotationQuat * this->forwardInModelSpace);
	this->vectorTop = glm::normalize(this->rotationQuat * this->topInModelSpace);
	this->vectorRight = glm::normalize(glm::cross(this->vectorForward, this->vectorTop));

	this->updateModelMatrix();
}

void Ship::update()
{
	updateModelMatrix();
}

float Ship::getLightConeHeight()
{
	return this->lightConeHeight;
}

float Ship::getLightConeBaseRadius()
{
	return this->lightConeBaseRadius;
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = glm::translate(position) * this->rotationMat * glm::scale(this->scale);
}




