#include "../../../../headers/graphics_techniques/bloom/hdr/HDRFramebuffer.h"

HDRFramebuffer::HDRFramebuffer(unsigned int windowWidth, unsigned int windowHeight)
{
    initFramebuffer();
    initColorBuffers(windowWidth, windowHeight);
    initDepthBuffer(windowWidth, windowHeight);
    specifyWhichColorBuffersWillBeUsedForRendering();
    checkIfFramebufferComplete();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRFramebuffer::initRenderingToThisFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HDRFramebuffer::endRenderingToThisFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int HDRFramebuffer::getSceneTexture()
{
    return colorBuffers[0];
}

unsigned int HDRFramebuffer::getBrightLightsTexture()
{
    return colorBuffers[1];
}

void HDRFramebuffer::initFramebuffer()
{
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
}

void HDRFramebuffer::initColorBuffers(unsigned int windowWidth, unsigned int windowHeight)
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

void HDRFramebuffer::initDepthBuffer(unsigned int windowWidth, unsigned int windowHeight)
{
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
}

void HDRFramebuffer::specifyWhichColorBuffersWillBeUsedForRendering()
{
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
}

void HDRFramebuffer::checkIfFramebufferComplete()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
}
