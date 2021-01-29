#pragma once

#include "glew.h"
#include "freeglut.h"
#include "BlurFramebuffer.h"
#include "../ScreenQuad.h"

class Blur
{
public:
	Blur(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur);
	void blur(ScreenQuad screenQuad, GLuint brightLightsTexture);
private:
	int blurAmount;
	GLuint programBlur;
	BlurFramebuffer blurFramebuffer;
};

