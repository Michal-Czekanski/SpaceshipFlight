#pragma once


#include <iostream>

#include "glew.h"
#include "freeglut.h"

class BloomTest
{
public:
	BloomTest(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend);

	/// <summary>
	/// Call this before rendering scene.
	/// </summary>
	void initRendering();
	/// <summary>
	/// Call this after rendering scene.
	/// </summary>
	void endRendering();

	/// <summary>
	/// Call this after endRendering() to blur bright fragments of the scene.
	/// </summary>
	void blur();


	/// <summary>
	/// Call this after blur to combine normal and blurred light scene.
	/// </summary>
	void finalBloomBlend();

	float exposure;
	float gamma;

	int blurAmount;

	float bloomAmount;
private:
	unsigned int hdrFBO;
	unsigned int colorBuffers[2];

	unsigned int blurFBOs[2];
	unsigned int blurColorBuffers[2];

	GLuint programBlur;
	GLuint programBloomFinalBlend;
	unsigned int quadVAO;

	void initFramebuffer(unsigned int windowWidth, unsigned int windowHeight);
	void initColorBuffers(unsigned int windowWidth, unsigned int windowHeight);
	void initDepthBuffer(unsigned int windowWidth, unsigned int windowHeight);
	void specifyWhichColorBuffersWillBeUsedForRendering();
	void checkIfFramebufferComplete();
	void initBlurFramebuffers(unsigned int windowWidth, unsigned int windowHeight);
	void initScreenQuad();
	void renderQuad();

	float quadVertices[4*5] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	
};

