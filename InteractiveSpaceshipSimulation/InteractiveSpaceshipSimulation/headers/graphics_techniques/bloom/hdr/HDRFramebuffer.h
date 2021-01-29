#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>

class HDRFramebuffer
{
public:
	HDRFramebuffer(unsigned int windowWidth, unsigned int windowHeight);

	void initRenderingToThisFBO();
	void endRenderingToThisFBO();
	
private:
	unsigned int hdrFBO;
	unsigned int colorBuffers[2];

	void initFramebuffer();
	void initColorBuffers(unsigned int windowWidth, unsigned int windowHeight);
	void initDepthBuffer(unsigned int windowWidth, unsigned int windowHeight);
	void specifyWhichColorBuffersWillBeUsedForRendering();
	void checkIfFramebufferComplete();
};

