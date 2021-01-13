#pragma once

#include "RenderableObject.h"

class Star : public RenderableObject
{
private:
	StarLight *light;

public:
	Star(glm::vec3 position, ModelData &modelData, glm::vec3 scale, StarLight *light, GLuint programDraw);

	StarLight* getLight();

	void draw(GLuint program, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
		std::vector<StarLight*>& starsLights);
};

