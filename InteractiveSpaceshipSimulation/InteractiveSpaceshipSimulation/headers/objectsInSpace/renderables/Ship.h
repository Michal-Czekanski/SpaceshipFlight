#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "utils/Calculations.h"
#include "RenderableObject.h"
#include "data/ShipLight.h"
#include "physics/IDynamicRigidbody.h"
#include "physics/RigidbodyFactory.h"
#include "utils/ShipPointer.h"
#include "objectsInSpace/renderables/IShip.h"

class Ship: public RenderableObject, public IDynamicRigidbody, public IShip
{
private:
	float speed = 0.0f;
	float pitchSpeed = 0.0f;
	float yawSpeed = 0.0f;
	float rollSpeed = 0.0f;

	void updateModelMatrix();

	ShipLight shipLight = ShipLight();

	float slowDownSpeed;

	int hp;
	const int maxHp = 5;

	void destroyed();

	bool isDestroyed = false;

public:
	/// <summary>
	/// Creates ship.
	/// </summary>
	/// <param name="position">Where to position ship.</param>
	/// <param name="rotationQuat">How to rotate ship on start.</param>
	Ship(glm::vec3 position, const RenderData& renderData, ShipLight shipLight,
		float shipSpeed, glm::vec3 scale, GLuint programDraw, TextureData textureData,
		float pitchSpeed = 100.0f, float yawSpeed = 100.0f, float rollSpeed = 100.0f,
		float slowDownSpeed = 1.05f);

	/// <summary>
	/// Moves ship forward based on ship speed -> updates ship's model matrix.
	/// </summary>
	void moveForward();

	/// <summary>
	/// Moves ship backwards based on ship speed -> updates ship's model matrix.
	/// </summary>
	void moveBackwards();

	/// <summary>
	/// Rotates ship.
	/// </summary>
	/// <param name="pitch">Value [-1, 1] specyfing in what direction and how much ship will pitch. (1 max up, -1 max down)</param>
	/// <param name="yaw">Value [-1, 1] specyfing in what direction and how much ship will yaw. (1 max right, -1 max left)</param>
	/// <param name="roll">Value [-1, 1] specyfing in what direction and how much ship will roll.(1 max right, -1 max left)</param>
	void rotateShip(float pitch, float yaw, float roll);

	ShipLight getShipLight();


	// Inherited via IDynamicRigidbody
	virtual PxRigidDynamic* getRigidDynamic() override;

	/// <summary>
	/// Updates Ship after physics body simulation update
	/// </summary>
	/// <param name="update"></param>
	virtual void physicsUpdate(RenderableUpdateData& update) override;

	void slowDown();

	int getHp();

	virtual void hit() override;
};

