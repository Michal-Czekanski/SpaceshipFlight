#include "../headers/Ship.h"

Ship::Ship(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop,
	float shipSpeed, float rotationSpeed,
	obj::Model shipModel, glm::quat rotationQuat,
	glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace): RenderableObject(position, rotationQuat, vectorForward, vectorTop, shipModel, shipTopInModelSpace, shipDirectionInModelSpace)
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
	if (pitchUp) { rotationAngleX -= rotationSpeed; };
	if (pitchDown) { rotationAngleX += rotationSpeed; };

	if (yawRight) { rotationAngleY -= rotationSpeed; };
	if (yawLeft) { rotationAngleY += rotationSpeed; };

	if (rollRigt) { rotationAngleZ += rotationSpeed; };
	if (rollLeft) { rotationAngleZ -= rotationSpeed; };


	this->rotationQuat = calculateRotationQuat(this->rotationQuat, rotationAngleX, rotationAngleY, rotationAngleZ);

	this->vectorForward = glm::normalize(this->rotationQuat * this->forwardInModelSpace);
	this->vectorTop = glm::normalize(this->rotationQuat * this->topInModelSpace);

	this->updateModelMatrix();
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = glm::translate(position) * glm::mat4_cast(this->rotationQuat);
}




