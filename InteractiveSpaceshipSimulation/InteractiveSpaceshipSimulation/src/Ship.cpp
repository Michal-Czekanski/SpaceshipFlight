#include "../headers/Ship.h"

Ship::Ship(glm::vec3 initialPosition, glm::vec3 initialShipDirection, glm::vec3 initialShipTop, 
	float shipSpeed, float rotationSpeed, 
	obj::Model shipModel, glm::quat initialRotationQuat,
	glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace)
{
	this->position = initialPosition;
	this->vectorForward = initialShipDirection;
	this->vectorTop = initialShipTop;
	this->speed = shipSpeed;
	this->rotationSpeed = rotationSpeed;
	this->shipModel = shipModel;
	this->rotationQuat = initialRotationQuat;
	this->modelMatrix = glm::translate(initialPosition) * glm::mat4_cast(initialRotationQuat);
	this->shipTopInModelSpace = shipTopInModelSpace;
	this->shipDirectionInModelSpace = shipDirectionInModelSpace;
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

	this->vectorForward = glm::normalize(this->rotationQuat * this->shipDirectionInModelSpace);
	this->vectorTop = glm::normalize(this->rotationQuat * this->shipTopInModelSpace);

	this->updateModelMatrix();
}

glm::mat4 Ship::getModelMatrix()
{
	return this->modelMatrix;
}

obj::Model Ship::getModel()
{
	return this->shipModel;
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = glm::translate(position) * glm::mat4_cast(this->rotationQuat);
}




