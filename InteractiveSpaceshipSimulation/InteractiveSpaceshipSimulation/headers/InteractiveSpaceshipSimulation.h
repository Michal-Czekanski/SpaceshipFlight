#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <cmath>
#include <vector>

#include "Scene.h"
#include "utils/Texture.h"
#include "utils/Shader_Loader.h"
#include "utils/Render_Utils.h"


#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720


GLuint programColor;
GLuint programAsteroidColor;

Core::Shader_Loader shaderLoader;

std::vector<AsteroidField*> asteroidFields;
bool debugHelpersOn = false;

void drawAsteroidColor(GLuint asteroidProgram, Asteroid* asteroid, obj::Model *asteroidModel, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color);

void initDebugHelpers(obj::Model sphereModel);

void renderDebugHelpers(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);