#include "objectsInSpace/renderables/Asteroid.h"

Asteroid::Asteroid(const RenderData& renderData, glm::vec3 position, glm::vec3 moveDirection, float speed,
	glm::vec3 scale, GLuint programDraw, TextureData textureData) :
	RenderableObject(position, renderData, scale, programDraw, textureData)
{
	this->speed = speed;
	this->moveDirection = moveDirection;
	rigidActor = RigidbodyFactory::createAsteroidRigidbody(position, rotationQuat, this);
}

void Asteroid::update()
{
	this->position += moveDirection * speed * Time::getDeltaTimeSec();
	this->positionMat = glm::translate(this->position);
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}

void Asteroid::addForce(PxVec3 force, PxForceMode::Enum mode, bool autowake)
{
	if (rigidActor)
	{
		((PxRigidDynamic*)rigidActor)->addForce(force, mode, autowake);
	}
}
