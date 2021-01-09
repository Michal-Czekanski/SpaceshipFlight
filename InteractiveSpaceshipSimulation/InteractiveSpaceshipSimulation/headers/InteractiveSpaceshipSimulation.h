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

Core::Shader_Loader shaderLoader;