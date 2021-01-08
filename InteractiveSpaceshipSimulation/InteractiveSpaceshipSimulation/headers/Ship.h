#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "utils/Calculations.h"
#include "CameraAttachable.h"

class Ship: public CameraAttachable
{
private:
	float speed;
	float rotationSpeed;
	glm::mat4 modelMatrix;

	obj::Model shipModel;

	glm::vec3 shipTopInModelSpace;
	glm::vec3 shipDirectionInModelSpace;

	void updateModelMatrix();

public:
	Ship(glm::vec3 initialPosition, glm::vec3 initialShipDirection, glm::vec3 initialShipTop, 
		float shipSpeed, float rotationSpeed, 
		obj::Model shipModel, glm::quat initialRotationQuat, 
		glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace);

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

	/// <summary>
	/// Returns ship model matrix.
	/// </summary>
	/// <returns>Ship model matrix.</returns>
	glm::mat4 getModelMatrix();

	/// <summary>
	/// Returns ship's model.
	/// </summary>
	/// <returns>Ship's model.</returns>
	obj::Model getModel();
};

