#include "../headers/Asteroid.h"

Asteroid::Asteroid(ModelData& modelData, glm::vec3 position, glm::vec3 moveDirection, float speed,
	glm::vec3 scale) :
	RenderableObject(position, modelData, scale)
{
	this->speed = speed;
	this->moveDirection = moveDirection;
}

void Asteroid::update()
{
	this->position += moveDirection * speed * Time::getDeltaTimeSec();
	this->positionMat = glm::translate(this->position);
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}
