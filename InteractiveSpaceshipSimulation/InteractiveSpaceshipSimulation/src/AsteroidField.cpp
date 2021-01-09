#include "../headers/AsteroidField.h"

AsteroidField::AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
	glm::vec3 position, glm::vec3 moveDirection, std::vector<obj::Model> asteroidModels,  glm::quat rotationQuat, glm::vec3 vectorTop):
	ObjectInSpace(position, rotationQuat, moveDirection, vectorTop)
{
	this->moveDirection = moveDirection;
	this->asteroidsCount = asteroidCount;
	this->initialPosition = position;

	for (int i = 0; i < asteroidCount; i++)
	{
		glm::vec3 asteroidPos = glm::ballRand(asteroidFieldRadius) + position;
		glm::vec3 scale = glm::vec3(randomFloat(minAsteroidScale, maxAsteroidScale));
		glm::quat rotationQuat = randomRotationQuat();
		obj::Model asteroidModel = asteroidModels[randomInt(0, asteroidModels.size() - 1)];

		Asteroid* asteroid = new Asteroid(asteroidPos, rotationQuat, glm::ballRand(1.0f), glm::ballRand(1.0f), asteroidModel,
			glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), scale, asteroidSpeed, moveDirection);
		this->asteroids.push_back(asteroid);
	}
}

std::vector<Asteroid*> AsteroidField::getAsteroids()
{
	return this->asteroids;
}
