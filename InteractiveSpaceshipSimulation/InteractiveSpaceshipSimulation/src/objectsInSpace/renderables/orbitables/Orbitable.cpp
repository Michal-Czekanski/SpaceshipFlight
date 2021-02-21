#include "objectsInSpace/renderables/orbitables/Orbitable.h"


Orbitable::Orbitable(glm::vec3 position, const RenderData& renderData, glm::vec3 scale,
	ObjectInSpace* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw, TextureData textureData) :
	RenderableObject(position, renderData, scale, programDraw, textureData)
	
{
	if (orbitAround)
	{
		this->orbitAround = orbitAround;
		this->orbitSpeed = orbitSpeed;

		this->initPosRelativeToOrbitCenter = position - orbitAround->getPosition();
		this->posRelativeToOrbitCenter = this->initPosRelativeToOrbitCenter;

		this->orbitPlane[1] = glm::normalize(orbitPlaneVec2);
		this->orbitPlane[0] = glm::normalize(this->posRelativeToOrbitCenter);

		this->orbitAxis = glm::normalize(glm::cross(this->orbitPlane[0], this->orbitPlane[1]));
	}
	else 
	{
		this->orbitSpeed = 0.0f;
	}
	
	rigidActor = RigidbodyFactory::createPlanetMoonStarRigidbody(position, rotationQuat, this);
}

void Orbitable::update()
{
	if (this->orbitAround)
	{
		orbit();
	}
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}

void Orbitable::orbit()
{
	if (this->orbitAround)
	{
		this->orbitQuat = calculateRotationQuatLocalAxises(this->orbitQuat, this->orbitPlane[1], this->orbitAxis, this->orbitPlane[0], 0.0f, this->orbitSpeed * Time::getDeltaTimeSec(), 0.0f);
		this->posRelativeToOrbitCenter = this->orbitQuat * this->initPosRelativeToOrbitCenter;
		this->position = this->posRelativeToOrbitCenter + this->orbitAround->getPosition();
		this->positionMat = glm::translate(this->position);
	}
}

glm::vec3 Orbitable::getOrbitCenterPos()
{
	return this->orbitAround->getPosition();
}

ObjectInSpace* Orbitable::getOrbitCenter()
{
	return this->orbitAround;
}


