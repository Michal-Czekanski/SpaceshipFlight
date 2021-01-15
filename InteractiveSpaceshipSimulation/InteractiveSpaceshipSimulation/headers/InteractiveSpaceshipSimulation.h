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


#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720


GLuint programColor;
/// <summary>
/// Used to draw planets, asteroids, moons.
/// </summary>
GLuint programColor2;
GLuint programStar;

Core::Shader_Loader shaderLoader;

std::vector<RenderableObject*> renderableObjects;
int renderableObjectsCount = 0;
std::vector<Planet*> planets; int planetsCount = 0;
std::vector<Star*> stars; int starsCount = 0; // Ugly code - everything should be on renderableObjects vector and call virtual method draw(), but there is no time for this right now.
std::vector<StarLight*> starsLights;
std::vector<Moon*> moons; int moonsCount = 0;
std::vector<AsteroidField*> asteroidFields;

bool debugHelpersOn = false;


void drawAsteroidColor(GLuint asteroidProgram, Asteroid* asteroid, obj::Model *asteroidModel, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::vec3 color);


/// <summary>
/// Renders object without lighting model.
/// </summary>
void drawObjectColor(GLuint program, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::mat4 modelMatrix,
	glm::vec3 color);

/// <summary>
/// Renders planet, moon or asteroid using given color with lighting model.
/// </summary>
/// <param name="stars">Stars that emit light.</param>
void drawObjectColor(GLuint program, RenderableObject* object, obj::Model* model, glm::mat4 perspectiveMatrix, 
	glm::mat4 cameraMatrix, glm::vec3 color, std::vector<Star*>& stars);

/// <summary>
/// Draws star with given color.
/// </summary>
void drawStarColor(GLuint program, Star* star, obj::Model* model, glm::mat4 perspectiveMatrix,
	glm::mat4 cameraMatrix, glm::vec3 color);

void initDebugHelpers(ModelData& sphereModelData);

void renderDebugHelpers(glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix);

void mouse(int x, int y);

void rotateShip();