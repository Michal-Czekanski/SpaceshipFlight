#include "objectsInSpace/renderables/Ship.h"


Ship::Ship(glm::vec3 position, const RenderData& renderData, ShipLight shipLight, float shipSpeed, glm::vec3 scale, GLuint programDraw, TextureData textureData,
	float pitchSpeed, float yawSpeed, float rollSpeed, float slowDownSpeed):
	RenderableObject(position, renderData, scale, programDraw, textureData), slowDownSpeed(slowDownSpeed),
	hp(maxHp)
{
	this->speed = shipSpeed;
	this->pitchSpeed = pitchSpeed;
	this->yawSpeed = yawSpeed;
	this->rollSpeed = rollSpeed;

	this->shipLight = shipLight;
	this->shipLight.update(this->position, this->getVectorForward());

	rigidActor = RigidbodyFactory::createShipRigidbody(position, rotationQuat, this);
}

void Ship::moveForward()
{
	if (rigidActor)
	{
		getRigidDynamic()->addForce(PhysxGLMConverter::vec3ToPxVec3(vectorForward * speed * Time::getDeltaTimeSec()));
	}
}

void Ship::moveBackwards()
{
	if (rigidActor)
	{
		getRigidDynamic()->addForce(PhysxGLMConverter::vec3ToPxVec3(-vectorForward * speed * Time::getDeltaTimeSec()));
	}
}

void Ship::rotateShip(float pitch, float yaw, float roll)
{
	pitch = glm::clamp(pitch, -1.0f, 1.0f);
	yaw = glm::clamp(yaw, -1.0f, 1.0f);
	roll = glm::clamp(roll, -1.0f, 1.0f);

	float rotationAngleX = pitchSpeed * pitch * Time::getDeltaTimeSec();
	float rotationAngleY = yawSpeed * (-yaw) * Time::getDeltaTimeSec();
	float rotationAngleZ = rollSpeed * roll * Time::getDeltaTimeSec();

	if (rigidActor)
	{
		getRigidDynamic()->setAngularVelocity(PhysxGLMConverter::vec3ToPxVec3(
			vectorForward * rotationAngleZ + vectorRight * rotationAngleX + vectorTop * rotationAngleY));
	}
	
}

ShipLight Ship::getShipLight()
{
	return this->shipLight;
}

PxRigidDynamic* Ship::getRigidDynamic()
{
	return (PxRigidDynamic*)rigidActor;
}

void Ship::physicsUpdate(RenderableUpdateData& update)
{
	RenderableObject::physicsUpdate(update);
	shipLight.update(position, vectorForward);
}

void Ship::slowDown()
{
	getRigidDynamic()->setLinearVelocity(getRigidDynamic()->getLinearVelocity() / slowDownSpeed);
}

int Ship::getHp()
{
	return hp;
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}




