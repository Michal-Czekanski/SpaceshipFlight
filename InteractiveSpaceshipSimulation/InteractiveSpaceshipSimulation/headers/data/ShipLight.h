#pragma once

#include "glm.hpp"
#include "ext.hpp"

/// <summary>
/// Ship's light is being emitted in a cone that's coming from ship's front.
/// </summary>
class ShipLight
{
private:
	float lightConeHeight;
	float lightConeBaseRadius;
	float lightStrength;
	glm::vec3 position;
	glm::vec3 lightDirection;
	glm::vec3 lightColor;
public:
	/// <summary>
	/// Creates ship's light.
	/// </summary>
	/// <param name="lightConeHeight"></param>
	/// <param name="lightConeBaseRadius"></param>
	/// <param name="position">Ship's position.</param>
	/// <param name="lightDirection">Ship's front direction.</param>
	/// <param name="lightColor"></param>
	ShipLight(float lightStrength, float lightConeHeight, float lightConeBaseRadius, glm::vec3 position, glm::vec3 lightDirection, glm::vec3 lightColor);

	/// <summary>
	/// Creates ship's light.
	/// </summary>
	/// <param name="lightConeHeight"></param>
	/// <param name="lightConeBaseRadius"></param>
	/// <param name="lightColor"></param>
	ShipLight(float lightStrength = 1.0f, float lightConeHeight = 800.0f, float lightConeBaseRadius = 300.0f, glm::vec3 lightColor = glm::vec3(1, 1, 1));

	/// <summary>
	/// Updates ship's light data.
	/// </summary>
	/// <param name="position">Ship's position.</param>
	/// <param name="lightDirection">Ship's direction.</param>
	void update(glm::vec3 position, glm::vec3 lightDirection);

	float getLightConeHeight();

	float getLightConeBaseRadius();

	glm::vec3 getPosition();

	glm::vec3 getLightDirection();

	glm::vec3 getLightColor();
};

