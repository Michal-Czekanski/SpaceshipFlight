#include "../headers/Ship.h"

Ship::Ship(glm::vec3 position, ModelData &modelData, ShipLight shipLight, 
	float shipSpeed, float rotationSpeed, glm::vec3 scale):
	RenderableObject(position, modelData, scale)
{
	this->speed = shipSpeed;
	this->rotationSpeed = rotationSpeed;

	this->shipLight = shipLight;
	this->shipLight.update(this->position, this->getVectorForward());
}

void Ship::moveForward()
{
	this->position += vectorForward * speed * Time::getDeltaTimeSec();
	this->positionMat = glm::translate(position);
	this->updateModelMatrix();
}

void Ship::moveBackwards()
{
	this->position -= vectorForward * speed * Time::getDeltaTimeSec();
	this->positionMat = glm::translate(position);
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

	this->updateDirections(this->rotationQuat);

	this->updateModelMatrix();
}

void Ship::update()
{
	updateModelMatrix();
	this->shipLight.update(this->position, this->getVectorForward());
}

ShipLight Ship::getShipLight()
{
	return this->shipLight;
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}




