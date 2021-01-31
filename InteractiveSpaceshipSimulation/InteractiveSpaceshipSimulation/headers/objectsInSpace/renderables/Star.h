#pragma once

#include "RenderableObject.h"

class Star : public RenderableObject
{
private:
	StarLight *light;

public:
	Star(glm::vec3 position, RenderData& renderData, glm::vec3 scale, StarLight *light, GLuint programDraw, GLuint texture);

	StarLight* getLight();

	void draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
		std::vector<StarLight*>& starsLights);
};

