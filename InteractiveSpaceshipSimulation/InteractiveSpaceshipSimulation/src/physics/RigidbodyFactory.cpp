#include "physics/RigidbodyFactory.h"

PxRigidDynamic* RigidbodyFactory::createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);
	float scale = ((RenderableObject*)shipPointer)->getScale().x;
	PxBoxGeometry geometry = PxBoxGeometry(1.9f / 2.0f * scale, 1.75f / 2.0f * scale, 6.0f / 2.0f * scale);
	return createDynamicRigidbody(position, rotation, shipPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createAsteroidRigidbody(glm::vec3 position, glm::quat rotation, void* asteroidPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);

	float scaleX = ((RenderableObject*)asteroidPointer)->getScale().x;
	float scaleY = ((RenderableObject*)asteroidPointer)->getScale().y;
	float scaleZ = ((RenderableObject*)asteroidPointer)->getScale().z;

	float scale = glm::max(scaleX, scaleY, scaleZ);

	PxSphereGeometry geometry = PxSphereGeometry(1.67f / 2.0f * scale);
	return createDynamicRigidbody(position, rotation, asteroidPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createPlanetMoonStarRigidbody(glm::vec3 position, glm::quat rotation, void* planetPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);
	PxSphereGeometry geometry = PxSphereGeometry(((RenderableObject*)planetPointer)->getScale().x);
	return createKinematicRigidbody(position, rotation, planetPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createDynamicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, PxMaterial* mat, PxGeometry& geometry)
{
	PxPhysics* pxPhysics = Physics::getInstance()->getPxPhysics();
	PxScene* pxScene = Physics::getInstance()->getPxScene();

	PxRigidDynamic* body = pxPhysics->createRigidDynamic(
		PxTransform(PhysxGLMConverter::vec3ToPxVec3(position), PhysxGLMConverter::quatToPxQuat(rotation)));

	PxShape* shape = pxPhysics->createShape(geometry, *mat);
	body->attachShape(*shape);
	shape->release();
	body->userData = userData;
	pxScene->addActor(*body);
	return body;
}

PxRigidDynamic* RigidbodyFactory::createKinematicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, PxMaterial* mat, PxGeometry& geometry)
{
	PxRigidDynamic* body = createDynamicRigidbody(position, rotation, userData, mat, geometry);
	body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	return body;
}
