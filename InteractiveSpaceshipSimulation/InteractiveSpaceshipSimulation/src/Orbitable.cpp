#include "../headers/Orbitable.h"


Orbitable::Orbitable(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, glm::vec3 scale,
	ObjectInSpace* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed):
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
	
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
	
}

void Orbitable::orbit()
{
	if (this->orbitAround)
	{
		this->orbitQuat = calculateRotationQuatLocalAxises(this->orbitQuat, this->orbitPlane[1], this->orbitAxis, this->orbitPlane[0], 0.0f, this->orbitSpeed, 0.0f);
		this->posRelativeToOrbitCenter = this->orbitQuat * this->initPosRelativeToOrbitCenter;
		this->position = this->posRelativeToOrbitCenter + this->orbitAround->getPosition();
	}
}
