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
#include "utils/Mouse.h"
#include "graphics_techniques/bloom/Bloom.h"
#include "Game.h"

GLuint programColor;
/// <summary>
/// Used to draw planets, asteroids, moons.
/// </summary>
GLuint programTexture;
GLuint programStar;
GLuint programInstanceColor;
GLuint programInstanceTexture;
GLuint programStarTexture;
GLuint programSkybox;


GLuint shipTexture;
GLuint shipNormalTexture;
GLuint starTextures[3]{0,0,0};
std::vector<GLuint> asteroidTextures;
std::vector<GLuint> asteroidNormalTextures;
std::vector<GLuint> planetTextures;
std::vector<GLuint> planetNormals;

GLuint skyboksik;
GLuint _skybox[6];

Core::Shader_Loader shaderLoader;

std::vector<RenderableObject*> renderableObjects;
int renderableObjectsCount = 0;
std::vector<StarLight*> starsLights;
std::vector<AsteroidField*> asteroidFields;

Bloom* bloom;

/// <summary>
/// Renders object without lighting model.
/// </summary>
void drawObjectColor(GLuint program, obj::Model* model, glm::mat4 perspectiveMatrix, glm::mat4 cameraMatrix, glm::mat4 modelMatrix,
	glm::vec3 color);

void mouse(int x, int y);

void rotateShip();