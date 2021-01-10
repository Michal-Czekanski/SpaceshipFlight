#include "../headers/Scene.h"

void initScene(obj::Model& shipModel, obj::Model& sphereModel, obj::Model& asteroidModel, Ship*& ship, AttachableCamera*& camera, std::vector<RenderableObject*>& renderableObjects, 
	int& renderableObjectsCount, std::vector<AsteroidField*>& asteroidFields, std::vector<Planet*>& planets, int& planetsCount, std::vector<Star*>& stars, int& starsCount)
{
	float star1Scale = 700.0f;

	glm::vec3 startingPlanetColor = glm::vec3(1.0f, 0.1f, 0.1f);

	ship = new Ship(initialShipPosition, initialShipDirection, initialShipTop, shipSpeed, shipRotationSpeed,
		shipModel, initialShipRotation, shipTopInModelSpace, shipDirectionInModelSpace, shipScale);
	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (ObjectInSpace*)ship);
	Planet* startingPlanet = new Planet(glm::vec3(0, 0, 25.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(10.0f));
	Star* star1 = new Star(glm::vec3(600.0f, -700.0f, 3000.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(star1Scale));

	Moon* moon = new Moon(glm::vec3(0, 0, -15.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(5.0f), startingPlanet, 
		glm::vec3(1, 1, 12), 1.0f);

	Star* star2 = new Star(glm::vec3(-900.0f, -600.0f, -5000.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(500.0f));

	Star* star3 = new Star(glm::vec3(-4000.0f, 1500.0f, -300.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(650.f));


	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	planets.push_back(startingPlanet); planetsCount++;
	stars.push_back(star1); starsCount++;
	renderableObjects.push_back((RenderableObject*)moon); renderableObjectsCount++;
	stars.push_back(star2); starsCount++;
	stars.push_back(star3); starsCount++;



	//generateRandomPlanetsForStar(star1, 20, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star1, 20, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModel);
	//generateRandomPlanetsForStar(star2, 25, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star2, 25, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModel);
	//generateRandomPlanetsForStar(star3, 22, 3, 50, 0.001f, 0.05f, renderableObjects, renderableObjectsCount, sphereModel);
	generateRandomPlanetsForStar(star3, 22, 3, 50, 0.001f, 0.05f, planets, planetsCount, sphereModel);

	std::vector<obj::Model> asteroidModels; asteroidModels.push_back(asteroidModel);
	AsteroidField* asteroidField1 = new AsteroidField(20, 30.0f, 1.0f, 1.0f, 7.0f, ship->getPosition() + glm::vec3(4.0f, 3.0f, 25.0f), glm::vec3(0, 0.1f, 1.0f), asteroidModels);
	asteroidFields.push_back(asteroidField1);

	generateRandomAsteroidFields(asteroidFields, 5, asteroidModels);
}

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, float minPlanetOrbitSpeed, float maxPlanetOrbitSpeed,
	std::vector<RenderableObject*> &renderableObjects, int &renderableObjectsCount, obj::Model &planetModel)
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

		Planet* planet = new Planet(planetPosRelativeToStar, planetModel, planetScale, star, orbitPlaneVec2, planetOrbitSpeed);
		renderableObjects.push_back(planet); renderableObjectsCount++;
	}
}

void generateRandomPlanetsForStar(Star* star, int howManyPlanetsGenerate, float minPlanetScale, float maxPlanetScale, float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<Planet*>& planets, int& gamePlanetsCounter, obj::Model& planetModel)
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

		Planet* planet = new Planet(planetPosRelativeToStar, planetModel, planetScale, star, orbitPlaneVec2, planetOrbitSpeed);
		planets.push_back(planet); gamePlanetsCounter++;
	}

}

void generateRandomAsteroidFields(std::vector<AsteroidField*>& fields, int count, std::vector<obj::Model> asteroidModels,
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

		AsteroidField* field = new AsteroidField(asteroidCount, fieldRadius, speed, minAsteroidScale, maxAsteroidScale, fieldPos, moveDirection, asteroidModels);
		fields.push_back(field);
	}
}
