#pragma once

#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>

#include "utils/Shader_Loader.h"
#include "utils/Render_Utils.h"
#include "utils/Camera.h"
#include "utils/Texture.h"
#include "Ship.h"



const glm::vec3 initialShipPosition = glm::vec3(0, 0, 0);

const glm::vec3 initialShipDirection = glm::vec3(0, 0, 1);

const glm::vec3 initialShipTop = glm::vec3(0, 1, 0);

const glm::quat initialShipRotation;

const float shipSpeed = 0.5f;

const float shipRotationSpeed = 0.25f;

const glm::vec3 shipDirectionInModelSpace = glm::vec3(0, 0, 1);

const glm::vec3 shipTopInModelSpace = glm::vec3(0, 1, 0);


glm::vec3 lightDir = glm::normalize(glm::vec3(1, -1, 1));