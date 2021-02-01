#pragma once

#include "objectsInSpace/ObjectInSpace.h"
#include "Asteroid.h"
#include <vector>
#include "utils/Calculations.h"
#include "utils/Texture.h"
#include "data/RenderDataInstancing.h"

class AsteroidField: public ObjectInSpace
{
public:
	/// <summary>
	/// Creates AsteroidField which generates random asteroids.
	/// </summary>
	AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
		glm::vec3 position, glm::vec3 moveDirection, std::vector<RenderDataInstancing>& renderDatas, GLuint programDraw,
		std::vector<TextureData>& asteroidsTexturesDatas,
		glm::vec3 vectorTop = glm::vec3(0, 0, 1), glm::vec3 asteroidColor = glm::vec3(0.3f));

	std::vector<Asteroid*> getAsteroids();

	void draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos,
		std::vector<StarLight*>& starsLights);

	void update();


private:
	std::vector<Asteroid*> asteroids;
	int asteroidsCount;
	glm::vec3 initialPosition;
	GLuint programDraw;
	glm::vec3 asteroidColor;
	std::vector<TextureData> texturesDatas;
	const std::vector<RenderDataInstancing> renderDatas;

	void generateRandomAsteroids(glm::vec3 generationCenter, glm::vec3 moveDirection, int asteroidsCount, 
		float asteroidFieldRadius, float asteroidSpeed,
		float minAsteroidScale, float maxAsteroidScale, 
		std::vector<RenderDataInstancing>& renderDatas, GLuint programDraw, glm::vec3 asteroidColor,
		std::vector<TextureData>& asteroidsTexturesDatas);

};