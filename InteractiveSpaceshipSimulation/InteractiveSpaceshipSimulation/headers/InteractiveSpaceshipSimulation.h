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
#include "Scene.h"
#include "utils/Calculations.h"
#include "AttachableCamera.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720


GLuint programColor;

Core::Shader_Loader shaderLoader;