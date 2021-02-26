#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include <cmath>
#include <vector>

#include "utils/Camera.h"
#include "objectsInSpace/renderables/Ship.h"
#include "utils/Calculations.h"
#include "AttachableCamera.h"
#include "objectsInSpace/renderables/orbitables/Planet.h"
#include "objectsInSpace/renderables/Star.h"
#include "objectsInSpace/renderables/RenderableObject.h"
#include "objectsInSpace/renderables/orbitables/Moon.h"
#include "objectsInSpace/renderables/Asteroid.h"
#include "objectsInSpace/renderables/AsteroidField.h"
#include "data/ModelData.h"
#include "data/Textures.h"

const glm::vec3 testLightDir = glm::vec3(0, 1, 1);

const glm::vec3 initShipPos = glm::vec3(0, 0, -40);

const glm::quat initialShipRotation = 
	calculateRotationQuatWorldAxises(glm::quat(), 0, glm::radians(180.0f), 0);


const float shipSpeed = 1000.0f;

const glm::vec3 initCameraLookDir = glm::vec3(0, 0, -1);

const float camOffsetMultiplier = 0.8f;
const float camUpOffsetMultiplier = 0.35f;

const glm::vec3 shipScale = glm::vec3(0.1f);

const glm::vec3 shipColor = glm::vec3(0.0f, 0.9f, 0.8f);

const glm::vec3 startPlanetPos = glm::vec3(0, 15.0f, 50.0f);
const glm::vec3 startPlanetScale = glm::vec3(25.0f);

const glm::vec3 star1Pos = glm::vec3(200.0f, -250.f, 3000.0f);
const glm::vec3 star1Scale = glm::vec3(700.0f);

const glm::vec3 star2Pos = glm::vec3(-900.0f, -600.0f, -5000.0f);
const glm::vec3 star2Scale = glm::vec3(500.0f);

const glm::vec3 star3Pos = glm::vec3(-4000.0f, 1500.0f, -300.0f);
const glm::vec3 star3Scale = glm::vec3(600.0f);

const glm::vec3 star4Pos = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 star4Scale = glm::vec3(7000.0f);

void initScene(const RenderData &shipRenderData, const RenderData& sphereRenderData, const RenderDataInstancing& asteroidRenderDataInstancing, 
	Ship* &ship, AttachableCamera* &camera,
	std::vector<RenderableObject*> &renderableObjects, int& renderableObjectsCount, 
	std::vector<AsteroidField*> &asteroidFields,
	std::vector<StarLight*> &starsLights,
	GLuint programTexture, GLuint programStar, GLuint programInstanceTexture,
	GLuint programStarTexture, Textures& textures);

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<RenderableObject*>& renderableObjects, int& renderableObjectsCount, const RenderData& planetRenderData, GLuint programDraw,
	std::vector<TextureData>& planetsTexturesDatas);
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
void generateRandomAsteroidFields(std::vector<AsteroidField*>& fields, int count, std::vector<RenderDataInstancing>& asteroidRenderDatas,
	GLuint programDraw, std::vector<TextureData>& asteroidsTexturesDatas,
	float generationRadius = 3000.0f, float minAsteroidFieldRadius = 100.0f, float maxAsteroidFieldRadius = 400.0f,
	float minAsteroidScale = 0.5f, float maxAsteroidScale = 5.0f,
	float minSpeed = 0.1f, float maxSpeed = 10.0f, int minAsteroidCount = 100, int maxAsteroidCount = 200);