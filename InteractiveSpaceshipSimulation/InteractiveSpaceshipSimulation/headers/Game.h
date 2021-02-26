#pragma once

#include "physics/Physics.h"
#include <vector>
#include "objectsInSpace/renderables/RenderableObject.h"

class Game
{
public:
	/// <summary>
	/// Updates positions of renderable objects using positions of objects from physics scene. Should be called after physics scene update.
	/// </summary>
	static void updateNormalScene();

	static void gameover();

	static int windowWidth;

	static int windowHeight;
};

