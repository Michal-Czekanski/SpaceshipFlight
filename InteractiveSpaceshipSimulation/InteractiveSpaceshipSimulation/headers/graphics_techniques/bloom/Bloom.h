#pragma once

#include "glew.h"
#include "freeglut.h"

#include "ScreenQuad.h"
#include "blur/Blur.h"
#include "hdr/HDRFramebuffer.h"

class Bloom
{
public:
	Bloom(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend);
private:
	GLuint programBloomFinalBlend;
	float exposure;
	float gamma;
	ScreenQuad screenQuad;
	Blur blur;
	HDRFramebuffer hdrFramebuffer;
};

