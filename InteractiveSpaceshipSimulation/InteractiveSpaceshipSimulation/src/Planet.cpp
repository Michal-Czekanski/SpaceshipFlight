#include "../headers/Planet.h"

Planet::Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
	glm::vec3 scale): 
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
{
	this->orbitSpeed = 0.0f;
}

Planet::Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, 
	glm::vec3 scale, Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed):
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
{
	this->orbitAround = orbitAround;
	this->orbitSpeed = orbitSpeed;

	this->orbitPlane[1] = glm::normalize(orbitPlaneVec2);
	glm::vec3 vecStarToPlanet = position - orbitAround->getPosition();
	this->posRelativeToStar = vecStarToPlanet;
	this->orbitPlane[0] = glm::normalize(vecStarToPlanet);

	this->orbitAxis = glm::normalize(glm::cross(this->orbitPlane[0], this->orbitPlane[1]));
}

void Planet::update()
{
	if (this->orbitAround)
	{
		this->orbitQuat = calculateRotationQuatLocalAxises(this->orbitQuat, this->orbitPlane[1], this->orbitAxis, this->orbitPlane[0], 0.0f, this->orbitSpeed, 0.0f);
		this->modelMatrix = glm::translate(this->orbitAround->getPosition()) * glm::mat4_cast(this->orbitQuat) * glm::translate(-this->orbitAround->getPosition()) * glm::translate(this->position) * glm::mat4_cast(this->rotationQuat) * glm::scale(this->scale);
	}
	else 
	{
		this->modelMatrix = glm::translate(this->position) * glm::mat4_cast(this->rotationQuat) * glm::scale(this->scale);
	}
}

