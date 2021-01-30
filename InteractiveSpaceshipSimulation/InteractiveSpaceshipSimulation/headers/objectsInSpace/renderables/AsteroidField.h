#pragma once

#include "objectsInSpace/ObjectInSpace.h"
#include "Asteroid.h"
#include <vector>
#include "utils/Calculations.h"
#include "utils/Texture.h"

class AsteroidField: public ObjectInSpace
{
private:
	std::vector<Asteroid*> asteroids;
	int asteroidsCount;
	glm::vec3 initialPosition;
	GLuint programDraw;
	Core::RenderContext renderContext;
	Core::RenderContext simplifiedRenderContext;
	glm::vec3 asteroidColor;
	std::vector<GLuint> asteroidTextures;

	void generateRandomAsteroids(glm::vec3 generationCenter, glm::vec3 moveDirection, int asteroidsCount, 
		float asteroidFieldRadius, float asteroidSpeed,
		float minAsteroidScale, float maxAsteroidScale, 
		std::vector<ModelData*> &modelsData, GLuint programDraw, glm::vec3 asteroidColor,
		std::vector<GLuint>& asteroidTextures);
public:
	/// <summary>
	/// Creates AsteroidField which generates random asteroids.
	/// </summary>
	/// <param name="asteroidCount"></param>
	/// <param name="asteroidFieldRadius"></param>
	/// <param name="asteroidSpeed"></param>
	/// <param name="minAsteroidScale"></param>
	/// <param name="maxAsteroidScale"></param>
	/// <param name="position"></param>
	/// <param name="moveDirection"></param>
	/// <param name="asteroidModels"></param>
	/// <param name="vectorTop"></param>
	AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
		glm::vec3 position, glm::vec3 moveDirection, std::vector<ModelData*>& modelsData, GLuint programDraw, 
		std::vector<GLuint>& asteroidTextures,
		glm::vec3 vectorTop = glm::vec3(0, 0, 1), glm::vec3 asteroidColor = glm::vec3(0.3f));

	std::vector<Asteroid*> getAsteroids();

	void draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
		std::vector<StarLight*>& starsLights);

	void update();
};