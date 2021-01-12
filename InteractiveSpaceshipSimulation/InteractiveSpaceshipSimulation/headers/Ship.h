#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "utils/Calculations.h"
#include "RenderableObject.h"
#include "data/ShipLight.h"

class Ship: public RenderableObject
{
private:
	float speed = 0.0f;
	float rotationSpeed = 0.0f;

	void updateModelMatrix();

	ShipLight shipLight = ShipLight();

public:
	/// <summary>
	/// Creates ship.
	/// </summary>
	/// <param name="position">Where to position ship.</param>
	/// <param name="shipModel"></param>
	/// <param name="shipLight"></param>
	/// <param name="shipSpeed"></param>
	/// <param name="rotationSpeed"></param>
	/// <param name="scale"></param>
	/// <param name="rotationQuat">How to rotate ship on start.</param>
	/// <param name="shipTopInModelSpace"></param>
	/// <param name="shipDirectionInModelSpace"></param>
	Ship(glm::vec3 position, ModelData &modelData, ShipLight shipLight,
		float shipSpeed, float rotationSpeed, glm::vec3 scale);

	/// <summary>
	/// Moves ship forward based on ship speed -> updates ship's model matrix.
	/// </summary>
	void moveForward();

	/// <summary>
	/// Moves ship backwards based on ship speed -> updates ship's model matrix.
	/// </summary>
	void moveBackwards();

	/// <summary>
	/// Rotates ship along given axises using ship's rotationSpeed -> updates ship's model matrix.
	/// </summary>
	/// <param name="pitchUp">Rotates up along X axix.</param>
	/// <param name="pitchDown">Rotates down along X axis.</param>
	/// <param name="yawRight">Rotates right along Y axis.</param>
	/// <param name="yawLeft">Rotates left along Y axis.</param>
	/// <param name="rollRigt">Rotates right along Z axis.</param>
	/// <param name="rollLeft">Rotates left along Z axis.</param>
	void rotateShip(bool pitchUp, bool pitchDown, bool yawRight, bool yawLeft, bool rollRigt, bool rollLeft);

	void update();

	ShipLight getShipLight();
};

