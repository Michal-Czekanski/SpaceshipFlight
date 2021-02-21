#pragma once
#include "RenderableObject.h"
#include "physics/IDynamicRigidbody.h"
#include "physics/RigidbodyFactory.h"

class Asteroid: public RenderableObject, public IDynamicRigidbody
{
private:
	float speed;
	glm::vec3 moveDirection;

public:
	Asteroid(const RenderData& renderData, glm::vec3 position, glm::vec3 moveDirection, float speed,
		glm::vec3 scale, GLuint programDraw, TextureData textureData);

	// Inherited via IDynamicRigidbody
	virtual PxRigidDynamic* getRigidDynamic() override;
};

