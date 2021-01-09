#include "../headers/Scene.h"

void initScene(obj::Model& shipModel, obj::Model& sphereModel, Ship* &ship, AttachableCamera* &camera, std::vector<RenderableObject*> &renderableObjects,
	int &renderableObjectsCount)
{
	float star1Scale = 700.0f;

	glm::vec3 startingPlanetColor = glm::vec3(1.0f, 0.1f, 0.1f);

	ship = new Ship(initialShipPosition, initialShipDirection, initialShipTop, shipSpeed, shipRotationSpeed,
		shipModel, initialShipRotation, shipTopInModelSpace, shipDirectionInModelSpace, shipScale);
	camera = new AttachableCamera(camOffsetMultiplier, camUpOffsetMultiplier, (ObjectInSpace*)ship);
	Planet* startingPlanet = new Planet(glm::vec3(0, 0, 5), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(3.0f));
	Star* star1 = new Star(glm::vec3(400.0f, -300.0f, 2000.0f), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(star1Scale));

	Planet* planet2 = new Planet(glm::vec3(0, 0, 15), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(3.0f),
		star1, glm::vec3(0, -3, 2), 0.00001f);

	Moon* moon = new Moon(glm::vec3(0, 0, -5), glm::quat(), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), sphereModel, glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(0.75f), startingPlanet, glm::vec3(1, 1, 12), 0.001f);

	renderableObjects.push_back((RenderableObject*)ship); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)startingPlanet); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)star1); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)planet2); renderableObjectsCount++;
	renderableObjects.push_back((RenderableObject*)moon); renderableObjectsCount++;

	generateRandomPlanetsForStar(star1, 20, 3, 50, 1, 20, renderableObjects, renderableObjectsCount, sphereModel);
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
		float planetOrbitSpeed = 0.00001f * randomFloat(minPlanetOrbitSpeed, maxPlanetOrbitSpeed);

		Planet* planet = new Planet(planetPosRelativeToStar, planetModel, planetScale, star, orbitPlaneVec2, planetOrbitSpeed);
		renderableObjects.push_back(planet); renderableObjectsCount++;
	}
}
