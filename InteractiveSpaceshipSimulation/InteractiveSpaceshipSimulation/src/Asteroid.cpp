#include "../headers/Asteroid.h"

Asteroid::Asteroid(ModelData& modelData, glm::vec3 position, glm::vec3 moveDirection, float speed,
	glm::vec3 scale, GLuint programDraw) :
	RenderableObject(position, modelData, scale, programDraw)
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
