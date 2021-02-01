#include "objectsInSpace/renderables/Asteroid.h"

Asteroid::Asteroid(const RenderData& renderData, glm::vec3 position, glm::vec3 moveDirection, float speed,
	glm::vec3 scale, GLuint programDraw, TextureData textureData) :
	RenderableObject(position, renderData, scale, programDraw, textureData)
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
