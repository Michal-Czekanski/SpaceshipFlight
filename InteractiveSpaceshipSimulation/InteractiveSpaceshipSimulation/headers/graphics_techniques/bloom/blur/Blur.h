#pragma once

#include "glew.h"
#include "freeglut.h"
#include "BlurFramebuffer.h"
#include "../ScreenQuad.h"

class Blur
{
public:
	Blur(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur);

	/// <summary>
	/// Blurs given bright lights texture and returns blurred texture id.
	/// </summary>
	/// <returns>Blurred texture id.</returns>
	GLuint blur(ScreenQuad screenQuad, GLuint brightLightsTexture);
private:
	int blurAmount;
	GLuint programBlur;
	BlurFramebuffer blurFramebuffer;
};

