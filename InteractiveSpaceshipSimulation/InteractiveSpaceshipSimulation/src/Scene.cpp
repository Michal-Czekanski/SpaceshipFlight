#include "../headers/Scene.h"

void initScene(ModelData& shipModelData, ModelData& sphereModelData, ModelData& asteroidModelData, Ship*& ship, AttachableCamera*& camera,
	std::vector<RenderableObject*>& renderableObjects, int& renderableObjectsCount,
	std::vector<AsteroidField*>& asteroidFields,
	std::vector<Planet*>& planets, int& planetsCount,
	std::vector<Star*>& stars, int& starsCount,
	std::vector<Moon*>& moons, int& moonsCount)
{
	ShipLight* shipLight = new ShipLight();
	
	ship = new Ship(initShipPos, shipModelData, *shipLight, shipSpeed, shipRotationSpeed, shipScale);
	//ship->rotate(initialShipRotation);

	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (ObjectInSpace*)ship);

	Planet* startingPlanet = new Planet(startPlanetPos, sphereModelData, startPlanetScale);

	Star* star1 = new Star(star1Pos, sphereModelData, star1Scale);


	//Moon* moon = new Moon(glm::vec3(0, 0, -15.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(5.0f), startingPlanet, 
	//	glm::vec3(1, 1, 12), 1.0f);

	Star* star2 = new Star(star2Pos, sphereModelData, star2Scale);

	Star* star3 = new Star(star3Pos, sphereModelData, star3Scale);



	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	planets.push_back(startingPlanet); planetsCount++;
	stars.push_back(star1); starsCount++;
	//renderableObjects.push_back((RenderableObject*)moon); renderableObjectsCount++;
	//moons.push_back(moon); moonsCount++;
	stars.push_back(star2); starsCount++;
	stars.push_back(star3); starsCount++;



	//generateRandomPlanetsForStar(star1, 20, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star1, 20, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModelData);
	//generateRandomPlanetsForStar(star2, 25, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star2, 25, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModelData);
	//generateRandomPlanetsForStar(star3, 22, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star3, 22, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModelData);

	std::vector<ModelData*> asteroidModelsData; asteroidModelsData.push_back(&asteroidModelData);
	
	AsteroidField* asteroidField1 = new AsteroidField(20, 30.0f, 1.0f, 1.0f, 7.0f, glm::vec3(4.0f, 3.0f, 25.0f), glm::vec3(0, 0.1f, 1.0f),
		asteroidModelsData);
	asteroidFields.push_back(asteroidField1);

	generateRandomAsteroidFields(asteroidFields, 5, asteroidModelsData);
}

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, float minPlanetOrbitSpeed, float maxPlanetOrbitSpeed,
	std::vector<RenderableObject*> &renderableObjects, int &renderableObjectsCount, ModelData& planetModelData)
{
	float randomPlanetGenerationRadius = star->getScale().x * 2;
	float pushPlanetsFromStarCenter = star->getScale().x;
	for (int i = 0; i < 20; i++)
	{
		glm::vec3 planetPosRelativeToStar = glm::ballRand(randomPlanetGenerationRadius) + star->getPosition();
		// push planet pos from star center
		glm::vec3 directionFromStarToPlanet = glm::normalize(planetPosRelativeToStar - star->getPosition());
		planetPosRelativeToStar += pushPlanetsFromStarCenter * directionFromStarToPlanet;

		glm::vec3 planetScale = glm::vec3(randomFloat(minPlanetScale, maxPlanetScale));
		glm::vec3 orbitPlaneVec2 = glm::ballRand(1.0f);
		float planetOrbitSpeed = randomFloat(minPlanetOrbitSpeed, maxPlanetOrbitSpeed);

		Planet* planet = new Planet(planetPosRelativeToStar, planetModelData, planetScale, star, orbitPlaneVec2, planetOrbitSpeed);
		renderableObjects.push_back(planet); renderableObjectsCount++;
	}
}

void generateRandomPlanetsForStar(Star* star, int howManyPlanetsGenerate, float minPlanetScale, float maxPlanetScale, 
	float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<Planet*>& planets, int& gamePlanetsCounter, ModelData &planetModelData)
{
	float randomPlanetGenerationRadius = star->getScale().x * 2;
	float pushPlanetsFromStarCenter = star->getScale().x;
	for (int i = 0; i < 20; i++)
	{
		glm::vec3 planetPosRelativeToStar = glm::ballRand(randomPlanetGenerationRadius) + star->getPosition();
		// push planet pos from star center
		glm::vec3 directionFromStarToPlanet = glm::normalize(planetPosRelativeToStar - star->getPosition());
		planetPosRelativeToStar += pushPlanetsFromStarCenter * directionFromStarToPlanet;

		glm::vec3 planetScale = glm::vec3(randomFloat(minPlanetScale, maxPlanetScale));
		glm::vec3 orbitPlaneVec2 = glm::ballRand(1.0f);
		float planetOrbitSpeed = randomFloat(minPlanetOrbitSpeed, maxPlanetOrbitSpeed);

		Planet* planet = new Planet(planetPosRelativeToStar, planetModelData, planetScale, star, orbitPlaneVec2, planetOrbitSpeed);
		planets.push_back(planet); gamePlanetsCounter++;
	}

}

void generateRandomAsteroidFields(std::vector<AsteroidField*>& fields, int count, std::vector<ModelData*> &asteroidModelsData,
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
			fieldPos, moveDirection, asteroidModelsData);
		fields.push_back(field);
	}
}
