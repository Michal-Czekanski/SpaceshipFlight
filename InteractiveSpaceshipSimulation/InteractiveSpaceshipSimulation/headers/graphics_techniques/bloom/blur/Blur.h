#pragma once

#include "glew.h"
#include "freeglut.h"
#include "BlurFramebuffer.h"

class Blur
{
public:
	Blur(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur);
private:
	int blurAmount;
	GLuint programBlur;
	BlurFramebuffer framebuffer;
};

