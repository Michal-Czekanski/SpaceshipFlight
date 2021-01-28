#pragma once

#include <iostream>

#include "glew.h"
#include "freeglut.h"

class FrameBufferTest
{
public:
	FrameBufferTest(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, GLuint programScreen);

    void initRenderingToThisFramebuffer();
    void endRenderingToThisFramebuffer();

    void renderScreenQuadTexture();

private:
    unsigned int framebuffer;
    unsigned int textureColorbuffer;
    const float quadVertices[6*4] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO;

    void createColorAttachmentTexture(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void createDepthAttachment(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void initScreenQuadVAO();

    void clearBufferContent();

    GLuint programScreen;
};

