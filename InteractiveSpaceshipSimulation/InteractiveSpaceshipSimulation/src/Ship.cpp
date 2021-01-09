#include "../headers/Ship.h"

Ship::Ship(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop,
	float shipSpeed, float rotationSpeed,
	obj::Model shipModel, glm::quat rotationQuat,
	glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace, glm::vec3 scale): 
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, shipModel, shipTopInModelSpace, shipDirectionInModelSpace, scale)
{
	this->speed = shipSpeed;
	this->rotationSpeed = rotationSpeed;
}

void Ship::moveForward()
{
	this->position += vectorForward * speed;
	this->updateModelMatrix();
}

void Ship::moveBackwards()
{
	this->position -= vectorForward * speed;
	this->updateModelMatrix();
}

void Ship::rotateShip(bool pitchUp, bool pitchDown, bool yawRight, bool yawLeft, bool rollRigt, bool rollLeft)
{
	float rotationAngleX = 0.0f; float rotationAngleY = 0.0f; float rotationAngleZ = 0.0f;
	if (pitchUp) { rotationAngleX += rotationSpeed; };
	if (pitchDown) { rotationAngleX -= rotationSpeed; };

	if (yawRight) { rotationAngleY -= rotationSpeed; };
	if (yawLeft) { rotationAngleY += rotationSpeed; };

	if (rollRigt) { rotationAngleZ += rotationSpeed; };
	if (rollLeft) { rotationAngleZ -= rotationSpeed; };


	this->rotationQuat = calculateRotationQuatLocalAxises(this->rotationQuat, this->vectorRight, this->vectorTop, this->vectorForward, rotationAngleX, rotationAngleY, rotationAngleZ);

	this->vectorForward = glm::normalize(this->rotationQuat * this->forwardInModelSpace);
	this->vectorTop = glm::normalize(this->rotationQuat * this->topInModelSpace);
	this->vectorRight = glm::normalize(glm::cross(this->vectorForward, this->vectorTop));

	this->updateModelMatrix();
}

void Ship::update()
{
	updateModelMatrix();
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = glm::translate(position) * glm::mat4_cast(this->rotationQuat) * glm::scale(this->scale);
}




