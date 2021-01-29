#include "BloomTest.h"

BloomTest::BloomTest(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend)
    : programBlur(programBlur), programBloomFinalBlend(programBloomFinalBlend), exposure(3.2f), gamma(1.0f), blurAmount(30),
    bloomAmount(1.0f)
{
    initFramebuffer(windowWidth, windowHeight);
    initBlurFramebuffers(windowWidth, windowHeight);
    initScreenQuad();

    glUseProgram(programBlur);
    glUniform1d(glGetUniformLocation(programBlur, "image"), 0);
    glUseProgram(programBloomFinalBlend);
    glUniform1d(glGetUniformLocation(programBloomFinalBlend, "scene"), 0);
    glUniform1d(glGetUniformLocation(programBloomFinalBlend, "bloomBlur"), 1);
}

void BloomTest::initRendering()
{
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BloomTest::endRendering()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BloomTest::blur()
{
    bool horizontal = true, first_iteration = true;
    int amount = blurAmount;
    glUseProgram(programBlur);
    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFBOs[horizontal]);
        glUniform1i(glGetUniformLocation(programBlur, "horizontal"), horizontal);
        glBindTexture(
            GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : blurColorBuffers[!horizontal]
        );
        renderQuad();
        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BloomTest::initFramebuffer(unsigned int windowWidth, unsigned int windowHeight)
{
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    
    initColorBuffers(windowWidth, windowHeight);
    initDepthBuffer(windowWidth, windowHeight);
    specifyWhichColorBuffersWillBeUsedForRendering();
    checkIfFramebufferComplete();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BloomTest::initColorBuffers(unsigned int windowWidth, unsigned int windowHeight)
{
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
        );
    }
}

void BloomTest::initDepthBuffer(unsigned int windowWidth, unsigned int windowHeight)
{
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
}

void BloomTest::specifyWhichColorBuffersWillBeUsedForRendering()
{
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
}

void BloomTest::checkIfFramebufferComplete()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
}

void BloomTest::initBlurFramebuffers(unsigned int windowWidth, unsigned int windowHeight)
{
    glGenFramebuffers(2, blurFBOs);

    glGenTextures(2, blurColorBuffers);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFBOs[i]);
        glBindTexture(GL_TEXTURE_2D, blurColorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurColorBuffers[i], 0
        );
        checkIfFramebufferComplete();
    }
}

void BloomTest::initScreenQuad()
{
    unsigned int quadVBO;
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void BloomTest::renderQuad()
{
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void BloomTest::finalBloomBlend()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programBloomFinalBlend);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    glUniform1i(glGetUniformLocation(programBloomFinalBlend, "scene"), 0);


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, blurColorBuffers[0]);
    glUniform1i(glGetUniformLocation(programBloomFinalBlend, "bloomBlur"), 1);


    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "exposure"), exposure);
    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "gamma"), gamma);
    renderQuad();
}
