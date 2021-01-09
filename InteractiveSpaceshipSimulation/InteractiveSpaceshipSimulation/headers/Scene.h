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


const glm::vec3 initialShipPosition = glm::vec3(0, 0, 0);

const glm::vec3 initialShipDirection = glm::vec3(0, 0, 1);

const glm::vec3 initialShipTop = glm::vec3(0, 1, 0);

const glm::quat initialShipRotation;

const float shipSpeed = 0.5f;

const float shipRotationSpeed = 0.25f;

const glm::vec3 shipDirectionInModelSpace = glm::vec3(0, 0, 1);

const glm::vec3 shipTopInModelSpace = glm::vec3(0, 1, 0);

const glm::vec3 initCameraLookDir = glm::vec3(0, 0, -1);

/// <summary>
/// Mock light, should be replaced with Star light and Ship light later.
/// </summary>
const glm::vec3 lightDir = glm::normalize(glm::vec3(1, -1, 1));

const float camOffsetMultiplier = 2.0f;
const float camUpOffsetMultiplier = 0.5f;

const glm::vec3 shipScale = glm::vec3(1.0f);

void initScene(obj::Model& shipModel, obj::Model& sphereModel, obj::Model& asteroidModel, Ship*& ship, AttachableCamera*& camera, std::vector<RenderableObject*>& renderableObjects,
	int& renderableObjectsCount);

void generateRandomPlanetsForStar(Star* star, int planetsCount, float minPlanetScale, float maxPlanetScale, float maxPlanetOrbitSpeed, float minPlanetOrbitSpeed,
	std::vector<RenderableObject*>& renderableObjects, int& renderableObjectsCount, obj::Model& planetModel);