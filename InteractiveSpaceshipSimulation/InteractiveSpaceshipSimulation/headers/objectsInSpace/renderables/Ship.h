#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "utils/Calculations.h"
#include "RenderableObject.h"
#include "data/ShipLight.h"
#include "physics/IDynamicRigidbody.h"

class Ship: public RenderableObject, public IDynamicRigidbody
{
private:
	float speed = 0.0f;
	float pitchSpeed = 0.0f;
	float yawSpeed = 0.0f;
	float rollSpeed = 0.0f;

	void updateModelMatrix();

	ShipLight shipLight = ShipLight();

public:
	/// <summary>
	/// Creates ship.
	/// </summary>
	/// <param name="position">Where to position ship.</param>
	/// <param name="rotationQuat">How to rotate ship on start.</param>
	Ship(glm::vec3 position, const RenderData& renderData, ShipLight shipLight,
		float shipSpeed, glm::vec3 scale, GLuint programDraw, TextureData textureData,
		float pitchSpeed = 1.0f, float yawSpeed = 1.0f, float rollSpeed = 1.0f);

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

	void update();

	ShipLight getShipLight();

	// Inherited via IDynamicRigidbody
	virtual void addForce(PxVec3 force, PxForceMode::Enum mode = PxForceMode::eFORCE, bool autowake = true) override;

};

