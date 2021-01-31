#include "objectsInSpace/renderables/Ship.h"


Ship::Ship(glm::vec3 position, RenderData& renderData, ShipLight shipLight, float shipSpeed, glm::vec3 scale, GLuint programDraw, GLuint shipTexture, GLuint shipNormalTexture,
	float pitchSpeed, float yawSpeed, float rollSpeed):
	RenderableObject(position, renderData, scale, programDraw, shipTexture, shipNormalTexture)
{
	this->speed = shipSpeed;
	this->pitchSpeed = pitchSpeed;
	this->yawSpeed = yawSpeed;
	this->rollSpeed = rollSpeed;

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

void Ship::rotateShip(float pitch, float yaw, float roll)
{
	pitch = glm::clamp(pitch, -1.0f, 1.0f);
	yaw = glm::clamp(yaw, -1.0f, 1.0f);
	roll = glm::clamp(roll, -1.0f, 1.0f);

	float rotationAngleX = pitchSpeed * pitch * Time::getDeltaTimeSec();
	float rotationAngleY = yawSpeed * (-yaw) * Time::getDeltaTimeSec();
	float rotationAngleZ = rollSpeed * roll * Time::getDeltaTimeSec();

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




