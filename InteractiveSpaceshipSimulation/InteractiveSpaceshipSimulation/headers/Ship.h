#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/objload.h"
#include "utils/Calculations.h"
#include "RenderableObject.h"

class Ship: public RenderableObject
{
private:
	float speed = 0.0f;
	float rotationSpeed = 0.0f;

	/// <summary>
	/// Ship has front light as a cone.
	/// </summary>
	float lightConeHeight;

	/// <summary>
	/// Ship has fron light as a cone.
	/// </summary>
	float lightConeBaseRadius;

	void updateModelMatrix();

	glm::vec3 lightColor;

public:
	/// <summary>
	/// Creates ship which has front light.
	/// </summary>
	/// <param name="position"></param>
	/// <param name="vectorForward"></param>
	/// <param name="vectorTop"></param>
	/// <param name="shipSpeed"></param>
	/// <param name="rotationSpeed"></param>
	/// <param name="shipModel"></param>
	/// <param name="rotationQuat">- Used to rotate ship.</param>
	/// <param name="shipTopInModelSpace"></param>
	/// <param name="shipDirectionInModelSpace">- Ship front in model space.</param>
	/// <param name="scale">- Used to scale ship.</param>
	/// <param name="lightConeHeight">- Ship's front light emits light as a cone. Specifies how far light will travel.</param>
	/// <param name="lightConeRadius">- Ship's front light emits light as a cone.</param>
	/// <param name="lightColor">- Ship's light color. </param>
	Ship(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop,
		float shipSpeed, float rotationSpeed,
		obj::Model shipModel, glm::quat rotationQuat,
		glm::vec3 shipTopInModelSpace, glm::vec3 shipDirectionInModelSpace, glm::vec3 scale,
		float lightConeHeight = 30.0f, float lightConeRadius = 10.0f, glm::vec3 lightColor = glm::vec3(0.980f, 0.976f, 0.917f));

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

	float getLightConeHeight();

	float getLightConeBaseRadius();

	glm::vec3 getLightColor();
};

