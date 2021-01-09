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
}

void Planet::update()
{
	if (this->orbitAround)
	{
		orbit();
	}
	this->modelMatrix = glm::translate(this->position) * glm::mat4_cast(this->rotationQuat) * glm::scale(this->scale);
}

