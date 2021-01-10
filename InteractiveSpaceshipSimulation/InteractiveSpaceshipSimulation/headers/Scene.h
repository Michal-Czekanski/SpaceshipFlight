#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include <cmath>
#include <vector>

#include "utils/Camera.h"
#include "Ship.h"
#include "utils/Calculations.h"
#include "AttachableCamera.h"
#include "Planet.h"
#include "Star.h"
#include "RenderableObject.h"
#include "Moon.h"
#include "Asteroid.h"
#include "AsteroidField.h"


const glm::vec3 initialShipPosition = glm::vec3(0, 0, 0);

const glm::vec3 initialShipDirection = glm::vec3(0, 0, 1);

const glm::vec3 initialShipTop = glm::vec3(0, 1, 0);

const glm::quat initialShipRotation;

const float shipSpeed = 100.0f;

const float shipRotationSpeed = 10.0f;

const glm::vec3 shipDirectionInModelSpace = glm::vec3(0, 0, 1);

const glm::vec3 shipTopInModelSpace = glm::vec3(0, 1, 0);

const glm::vec3 initCameraLookDir = glm::vec3(0, 0, -1);

/// <summary>
/// Mock light, should be replaced with Star light and Ship light later.
/// </summary>
const glm::vec3 lightDir = glm::normalize(glm::vec3(1, -1, 1));

const float camOffsetMultiplier = 2.0f;
const float camUpOffsetMultiplier = 0.5f;

const glm::vec3 shipScale = glm::vec3(0.6f);

void initScene(obj::Model& shipModel, obj::Model& sphereModel, obj::Model& asteroidModel, Ship*& ship, AttachableCamera*& camera, std::vector<RenderableObject*>& renderableObjects,
	int& renderableObjectsCount, std::vector<AsteroidField*> &asteroidFields, std::vector<Planet*>& planets, int &planetsCount, std::vector<Star*>& stars, int &starsCount,
	std::vector<Moon*> &moons, int &moonsCount);

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<RenderableObject*>& renderableObjects, int& renderableObjectsCount, obj::Model& planetModel);

void generateRandomPlanetsForStar(Star* star, int howManyPlanetsGenerate, float minPlanetScale, float maxPlanetScale, float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<Planet*>& planets, int& gamePlanetsCounter, obj::Model& planetModel);

/// <summary>
/// Generates asteroid fields randomly across world space.
/// </summary>
/// <param name="fields">Vector where asteroid fields will be stored.</param>
/// <param name="count">Asteroid fields count.</param>
/// <param name="asteroidModels">Vector of possible asteroid models.</param>
/// <param name="generationRadius">Radius in which asteroid fields will be generated from center of the world.</param>
/// <param name="minAsteroidFieldRadius">Each asteroid field generates asteroids in given radius. This value will be randomized.</param>
/// <param name="maxAsteroidFieldRadius">Each asteroid field generates asteroids in given radius. This value will be randomized.</param>
/// <param name="minAsteroidScale">Minimal asteroid scale.</param>
/// <param name="maxAsteroidScale">Maximal asteroid scale.</param>
/// <param name="minSpeed">Minimum asteroid field speed.</param>
/// <param name="maxSpeed">Maximum asteroid field speed.</param>
/// <param name="minAsteroidCount">Minimal asteroid count of one asteroid field.</param>
/// <param name="maxAsteroidCount">Maximal asteroid count of one asteroid field.</param>
void generateRandomAsteroidFields(std::vector<AsteroidField*>& fields, int count, std::vector<obj::Model> asteroidModels, 
	float generationRadius = 500.0f, float minAsteroidFieldRadius = 30.0f, float maxAsteroidFieldRadius = 70.0f,
	float minAsteroidScale = 0.5f, float maxAsteroidScale = 5.0f,
	float minSpeed = 0.1f, float maxSpeed = 10.0f, int minAsteroidCount = 30, int maxAsteroidCount = 100);