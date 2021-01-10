#include "../headers/Planet.h"

Planet::Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
	glm::vec3 scale) :
	Orbitable(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale, NULL, glm::vec3(), 0.0f)
{
	this->orbitSpeed = 0.0f;
}

Planet::Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, 
	glm::vec3 scale, Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed):
	Orbitable(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale, orbitAround, orbitPlaneVec2, orbitSpeed)
{
	this->orbitAround = orbitAround;
}

Planet::Planet(glm::vec3 position, obj::Model model, glm::vec3 scale, Star* orbitAround, glm::vec3 orbitPlaneVec2, 
	float orbitSpeed, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace):
	Orbitable(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale, orbitAround, orbitPlaneVec2, orbitSpeed)
{
	this->orbitAround = orbitAround;
}

void Planet::update()
{
	if (this->orbitAround)
	{
		orbit();
	}
	this->modelMatrix = glm::translate(this->position) * this->rotationMat * glm::scale(this->scale);
}

Star* Planet::getOrbitCenter()
{
	return this->orbitAround;
}

