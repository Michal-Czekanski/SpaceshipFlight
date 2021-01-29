#pragma once

#include "glew.h"
#include "freeglut.h"

class ScreenQuad
{
public:
	ScreenQuad();
private:
	unsigned int quadVAO;
	float quadVertices[4 * 5] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};


};

