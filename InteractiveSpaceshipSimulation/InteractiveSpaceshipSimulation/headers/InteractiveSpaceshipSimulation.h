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
#include "Mouse.h"
#include "../FrameBufferTest.h"


#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720


GLuint programColor;
/// <summary>
/// Used to draw planets, asteroids, moons.
/// </summary>
GLuint programColor2;
GLuint programStar;
GLuint programInstanceColor;
GLuint programStarTexture;

GLuint starTextures[3]{0,0,0};

Core::Shader_Loader shaderLoader;

std::vector<RenderableObject*> renderableObjects;
int renderableObjectsCount = 0;
std::vector<StarLight*> starsLights;
std::vector<AsteroidField*> asteroidFields;

bool debugHelpersOn = false;


/// <summary>
/// Renders object without lighting model.
/// </summary>
void drawObjectColor(GLuint program, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::mat4 modelMatrix,
	glm::vec3 color);

void initDebugHelpers(ModelData& sphereModelData);

void renderDebugHelpers(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);

void mouse(int x, int y);

void rotateShip();

FrameBufferTest* frameBufferTest;