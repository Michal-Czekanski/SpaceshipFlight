#include "objectsInSpace/renderables/Asteroid.h"

Asteroid::Asteroid(const RenderData& renderData, glm::vec3 position, glm::vec3 moveDirection, float speed,
	glm::vec3 scale, GLuint programDraw, TextureData textureData) :
	RenderableObject(position, renderData, scale, programDraw, textureData)
{
	this->speed = speed;
	this->moveDirection = moveDirection;
	rigidActor = RigidbodyFactory::createAsteroidRigidbody(position, rotationQuat, this);
	getRigidDynamic()->setLinearVelocity(PhysxGLMConverter::vec3ToPxVec3(moveDirection * speed));
}

PxRigidDynamic* Asteroid::getRigidDynamic()
{
	return (PxRigidDynamic*)rigidActor;
}
