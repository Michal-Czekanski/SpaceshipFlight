#include "objectsInSpace/renderables/AsteroidField.h"



AsteroidField::AsteroidField(int asteroidCount, float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale,
	glm::vec3 position, glm::vec3 moveDirection, std::vector<ModelData*>& modelsData, 
	GLuint programDraw, glm::vec3 vectorTop, glm::vec3 asteroidColor):
	ObjectInSpace(position, moveDirection, vectorTop)
{
	this->asteroidsCount = asteroidCount;
	this->initialPosition = position;
	this->programDraw = programDraw;
	obj::Model model = modelsData[0]->getModel(); this->renderContext.initFromOBJ(model);
	this->renderContext.initInstanceBuffer();
	obj::Model simplifiedModel = modelsData[0]->getSimplifiedModel();
	this->simplifiedRenderContext.initFromOBJ(simplifiedModel);
	this->simplifiedRenderContext.initInstanceBuffer();
	this->asteroidColor = asteroidColor;

	generateRandomAsteroids(position, moveDirection, asteroidCount, asteroidFieldRadius, asteroidSpeed, minAsteroidScale, maxAsteroidScale,
		modelsData, programDraw, asteroidColor);
}

void AsteroidField::generateRandomAsteroids(glm::vec3 generationCenter, glm::vec3 moveDirection, int asteroidsCount, 
	float asteroidFieldRadius, float asteroidSpeed, float minAsteroidScale, float maxAsteroidScale, std::vector<ModelData*>& modelsData, 
	GLuint programDraw, glm::vec3 asteroidColor)
{
	for (int i = 0; i < asteroidsCount; i++)
	{
		glm::vec3 asteroidPos = glm::ballRand(asteroidFieldRadius) + position;
		glm::vec3 scale = glm::vec3(randomFloat(minAsteroidScale, maxAsteroidScale));
		glm::quat rotationQuat = randomRotationQuat();
		ModelData* modelData = modelsData[randomInt(0, modelsData.size() - 1)];

		Asteroid* asteroid = new Asteroid(*modelData, asteroidPos, moveDirection, asteroidSpeed, scale, 
			programDraw);
		asteroid->setColor(asteroidColor);
		asteroid->rotate(rotationQuat);
		this->asteroids.push_back(asteroid);
	}
}

std::vector<Asteroid*> AsteroidField::getAsteroids()
{
	return this->asteroids;
}

void AsteroidField::draw(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, ShipLight shipLight, glm::vec3 camPos, std::vector<StarLight*>& starsLights)
{
	glUseProgram(programDraw);

	std::vector<glm::mat4> modelMatrixes;
	for (int i = 0; i < asteroids.size(); i++)
	{
		modelMatrixes.push_back(asteroids[i]->getModelMatrix());
	}

	glUniformMatrix4fv(glGetUniformLocation(programDraw, "perspectiveMatrix"), 1, GL_FALSE, (float*)&perspectiveMatrix);
	glUniformMatrix4fv(glGetUniformLocation(programDraw, "cameraMatrix"), 1, GL_FALSE, (float*)&cameraMatrix);

	glm::vec3 shipPosition = shipLight.getPosition();
	glUniform3f(glGetUniformLocation(programDraw, "shipPos"), shipPosition.x, shipPosition.y, shipPosition.z);
	glm::vec3 shipDirection = shipLight.getLightDirection();
	glUniform3f(glGetUniformLocation(programDraw, "shipDirection"), shipDirection.x, shipDirection.y, shipDirection.z);

	glUniform1f(glGetUniformLocation(programDraw, "shipLightConeHeight"), shipLight.getLightConeHeight());
	glUniform1f(glGetUniformLocation(programDraw, "shipLightConeRadius"), shipLight.getLightConeBaseRadius());
	glUniform3f(glGetUniformLocation(programDraw, "shipLightColor"),
		shipLight.getLightColor().x, shipLight.getLightColor().y, shipLight.getLightColor().z);

	glUniform3f(glGetUniformLocation(programDraw, "objectColor"), asteroidColor.x, asteroidColor.y, asteroidColor.z);
	glUniform3f(glGetUniformLocation(programDraw, "cameraPos"), camPos.x, camPos.y, camPos.z);


	std::vector<glm::vec3> starsPos;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsPos.push_back(starsLights[i]->getPosition());
	}
	glUniform3fv(glGetUniformLocation(programDraw, "starsPos"), starsLights.size(), reinterpret_cast<GLfloat*>(starsPos.data()));

	std::vector<float> starsLightStr;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsLightStr.push_back(starsLights[i]->getStrength());
	}
	glUniform1fv(glGetUniformLocation(programDraw, "starsLightStr"), starsLights.size(), reinterpret_cast<GLfloat*>(starsLightStr.data()));

	std::vector<glm::vec3> starsLightCol;
	for (int i = 0; i < starsLights.size(); i++)
	{
		starsLightCol.push_back(starsLights[i]->getColor());
	}
	glUniform3fv(glGetUniformLocation(programDraw, "starsLightCol"), starsLights.size(), reinterpret_cast<GLfloat*>(starsLightCol.data()));

	DiscreteLOD dlod = DiscreteLOD();
	float distFromCam = glm::distance(position, camPos);
	Core::RenderContext chosenContext = dlod.whichContextUse(distFromCam, simplifiedRenderContext, renderContext);
	Core::DrawContextInstanced(chosenContext, asteroids.size(), modelMatrixes);
	glUseProgram(0);
}

void AsteroidField::update()
{
	for (Asteroid* asteroid : asteroids)
	{
		asteroid->update();
	}
}
