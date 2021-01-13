#include "../headers/AsteroidField.h"



AsteroidField::AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
	glm::vec3 position, glm::vec3 moveDirection, std::vector<ModelData*>& modelsData, GLuint programDraw, glm::vec3 vectorTop):
	ObjectInSpace(position, moveDirection, vectorTop)
{
	this->asteroidsCount = asteroidCount;
	this->initialPosition = position;

	generateRandomAsteroids(position, moveDirection, asteroidCount, asteroidFieldRadius, asteroidSpeed, minAsteroidScale, maxAsteroidScale,
		modelsData, programDraw);
}

void AsteroidField::generateRandomAsteroids(glm::vec3 generationCenter, glm::vec3 moveDirection, int asteroidsCount, 
	float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale, std::vector<ModelData*>& modelsData, 
	GLuint programDraw)
{
	for (int i = 0; i < asteroidsCount; i++)
	{
		glm::vec3 asteroidPos = glm::ballRand(asteroidFieldRadius) + position;
		glm::vec3 scale = glm::vec3(randomFloat(minAsteroidScale, maxAsteroidScale));
		glm::quat rotationQuat = randomRotationQuat();
		ModelData* modelData = modelsData[randomInt(0, modelsData.size() - 1)];

		Asteroid* asteroid = new Asteroid(*modelData, asteroidPos, moveDirection, asteroidSpeed, scale, programDraw);
		asteroid->rotate(rotationQuat);
		this->asteroids.push_back(asteroid);
	}
}

std::vector<Asteroid*> AsteroidField::getAsteroids()
{
	return this->asteroids;
}
