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

	unsigned int getSceneTexture();
	unsigned int getBrightLightsTexture();
	
private:
	unsigned int FBO;
	unsigned int colorBuffers[2];

	void initFramebuffer();
	void initColorBuffers(unsigned int windowWidth, unsigned int windowHeight);
	void initDepthBuffer(unsigned int windowWidth, unsigned int windowHeight);
	void specifyWhichColorBuffersWillBeUsedForRendering();
	void checkIfFramebufferComplete();
};

