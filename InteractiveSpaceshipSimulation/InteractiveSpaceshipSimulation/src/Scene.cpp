#include "../headers/Scene.h"

void initScene(const RenderData& shipRenderData, const RenderData& sphereRenderData, const RenderDataInstancing& asteroidRenderDataInstancing,
	Ship*& ship, AttachableCamera*& camera,
	std::vector<RenderableObject*>& renderableObjects, int& renderableObjectsCount,
	std::vector<AsteroidField*>& asteroidFields,
	std::vector<StarLight*> &starsLights,
	GLuint programTexture, GLuint programStar, GLuint programInstanceTexture,
	GLuint programStarTexture, Textures& textures)
{
	ShipLight* shipLight = new ShipLight();
	
	ship = new Ship(initShipPos, shipRenderData, *shipLight, shipSpeed, shipScale, programTexture, textures.getShipTextureData());

	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (ObjectInSpace*)ship);

	ship->rotate(calculateRotationQuatWorldAxises(glm::quat(), 0, glm::radians(180.0f), 0));

	Planet* startingPlanet = new Planet(startPlanetPos, sphereRenderData, startPlanetScale, programTexture, textures.getPlanetsTexturesDatas()[0]);
	startingPlanet->setColor(glm::vec3(0.7, 0.1, 0.1f));

	StarLight* star1Light = new StarLight(); starsLights.push_back(star1Light);
	StarLight* star2Light = new StarLight(); starsLights.push_back(star2Light);
	StarLight* star3Light = new StarLight(); starsLights.push_back(star3Light);


	Star* star1 = new Star(star1Pos, sphereRenderData, star1Scale, star1Light, programStarTexture, textures.getStarsTexturesDatas()[0]);

	Moon* moon = new Moon(glm::vec3(0, 0, -15.0f), sphereRenderData, glm::vec3(8.0f), startingPlanet, glm::vec3(0, 0.5f, 1.0f), 0.01f, programTexture,
		textures.getMoonsTexturesDatas()[0]);
	Star* star2 = new Star(star2Pos, sphereRenderData, star2Scale, star2Light, programStarTexture, textures.getStarsTexturesDatas()[1]);

	Star* star3 = new Star(star3Pos, sphereRenderData, star3Scale, star3Light, programStarTexture, textures.getStarsTexturesDatas()[2]);


	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	renderableObjects.push_back(startingPlanet); renderableObjectsCount++;
	renderableObjects.push_back(star1); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)moon); renderableObjectsCount++;
	renderableObjects.push_back(star2); renderableObjectsCount++;
	renderableObjects.push_back(star3); renderableObjectsCount++;


	generateRandomPlanetsForStar(star1, 20, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereRenderData, programTexture,
		textures.getPlanetsTexturesDatas());
	
	generateRandomPlanetsForStar(star2, 25, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereRenderData, programTexture,
		textures.getPlanetsTexturesDatas());
	
	generateRandomPlanetsForStar(star3, 22, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereRenderData, programTexture,
		textures.getPlanetsTexturesDatas());

	std::vector<RenderDataInstancing> asteroidRenderDatas; asteroidRenderDatas.push_back(asteroidRenderDataInstancing);
	
	AsteroidField* asteroidField1 = 
		new AsteroidField(20, 30.0f, 5.0f, 1.0f, 7.0f, glm::vec3(4.0f, 3.0f, -25.0f), glm::vec3(0, 0.1f, 1.0f),
			asteroidRenderDatas, programInstanceTexture, textures.getAsteroidTexturesDatas());
	asteroidFields.push_back(asteroidField1);

	generateRandomAsteroidFields(asteroidFields, 55, asteroidRenderDatas, programInstanceTexture, textures.getAsteroidTexturesDatas());
}

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, 
	float minPlanetOrbitSpeed, float maxPlanetOrbitSpeed,
	std::vector<RenderableObject*> &renderableObjects, int &renderableObjectsCount, const RenderData& planetRenderData, GLuint programDraw,
	std::vector<TextureData>& planetsTexturesDatas)
{
	float randomPlanetGenerationRadius = star->getScale().x * 2;
	float pushPlanetsFromStarCenter = star->getScale().x;
	int v;
	for (int i = 0; i < 20; i++)
	{
		v = rand() % planetsTexturesDatas.size();
		glm::vec3 planetPosRelativeToStar = glm::ballRand(randomPlanetGenerationRadius) + star->getPosition();
		// push planet pos from star center
		glm::vec3 directionFromStarToPlanet = glm::normalize(planetPosRelativeToStar - star->getPosition());
		planetPosRelativeToStar += pushPlanetsFromStarCenter * directionFromStarToPlanet;

		glm::vec3 planetScale = glm::vec3(randomFloat(minPlanetScale, maxPlanetScale));
		glm::vec3 orbitPlaneVec2 = glm::ballRand(1.0f);
		float planetOrbitSpeed = randomFloat(minPlanetOrbitSpeed, maxPlanetOrbitSpeed);

		Planet* planet = new Planet(planetPosRelativeToStar, planetRenderData, planetScale, star, orbitPlaneVec2, planetOrbitSpeed,
			programDraw, planetsTexturesDatas[v]);
		renderableObjects.push_back(planet); renderableObjectsCount++;
	}
}

void generateRandomAsteroidFields(std::vector<AsteroidField*>& fields, int count, std::vector<RenderDataInstancing>& asteroidRenderDatas,
	GLuint programDraw, std::vector<TextureData>& asteroidsTexturesDatas,
	float generationRadius, float minAsteroidFieldRadius, float maxAsteroidFieldRadius,
	float minAsteroidScale, float maxAsteroidScale,
	float minSpeed, float maxSpeed, int minAsteroidCount, int maxAsteroidCount)
{
	for (int i = 0; i < count; i++)
	{
		int asteroidCount = randomInt(minAsteroidCount, maxAsteroidCount);
		float fieldRadius = randomFloat(minAsteroidFieldRadius, maxAsteroidFieldRadius);
		float speed = randomFloat(minSpeed, maxSpeed);

		glm::vec3 fieldPos = glm::ballRand(generationRadius);
		glm::vec3 moveDirection = glm::ballRand(1.0f);

		AsteroidField* field = new AsteroidField(asteroidCount, fieldRadius, speed, minAsteroidScale, maxAsteroidScale, 
			fieldPos, moveDirection, asteroidRenderDatas, programDraw, asteroidsTexturesDatas);
		fields.push_back(field);
	}
}
