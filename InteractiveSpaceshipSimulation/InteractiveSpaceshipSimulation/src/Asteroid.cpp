#include "../headers/Asteroid.h"

Asteroid::Asteroid(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
	glm::vec3 scale, float speed, glm::vec3 moveDirection) :
	RenderableObject(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale)
{
	this->speed = speed;
	this->moveDirection = moveDirection;
}

void Asteroid::update()
{
	this->position += moveDirection * speed * Time::getDeltaTimeSec();
	this->modelMatrix = glm::translate(this->position) * glm::mat4_cast(this->rotationQuat) * glm::scale(this->scale);
}
