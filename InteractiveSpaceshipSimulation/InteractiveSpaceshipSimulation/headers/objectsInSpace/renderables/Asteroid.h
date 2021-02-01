#pragma once
#include "RenderableObject.h"

class Asteroid: public RenderableObject
{
private:
	float speed;
	glm::vec3 moveDirection;

public:
	Asteroid(const RenderData& renderData, glm::vec3 position, glm::vec3 moveDirection, float speed,
		glm::vec3 scale, GLuint programDraw, TextureData textureData);

	void update();
};

