#pragma once

#include "ObjectInSpace.h"
#include "Asteroid.h"
#include <vector>
#include "utils/Calculations.h"

class AsteroidField: public ObjectInSpace
{
private:
	glm::vec3 moveDirection;
	std::vector<Asteroid*> asteroids;
	int asteroidsCount;
	glm::vec3 initialPosition;
	glm::vec3 position;
public:
	AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
		glm::vec3 position, glm::vec3 moveDirection, std::vector<obj::Model> asteroidModels,
		glm::quat rotationQuat = glm::quat(), glm::vec3 vectorTop = glm::vec3(0, 0, 1));

	std::vector<Asteroid*> getAsteroids();
};