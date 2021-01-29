#include "FrameBufferTest.h"

FrameBufferTest::FrameBufferTest(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, GLuint programScreen) :
    programScreen(programScreen), gamma(1.0f), exposure(4.18f)
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    createColorAttachmentTexture(SCR_WIDTH, SCR_HEIGHT);
    createDepthAttachment(SCR_WIDTH, SCR_HEIGHT);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    initScreenQuadVAO();
}

void FrameBufferTest::createColorAttachmentTexture(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
}

void FrameBufferTest::createDepthAttachment(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void FrameBufferTest::initScreenQuadVAO()
{
    unsigned int quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void FrameBufferTest::clearBufferContent()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBufferTest::initRenderingToThisFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);

    clearBufferContent();
}

void FrameBufferTest::endRenderingToThisFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferTest::renderScreenQuadTexture()
{
    glUseProgram(programScreen);
    //glUniform1i(glGetUniformLocation(programScreen, "screenTexture"), 0);

    glUniform1f(glGetUniformLocation(programScreen, "gamma"), gamma);
    glUniform1f(glGetUniformLocation(programScreen, "exposure"), exposure);


    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
