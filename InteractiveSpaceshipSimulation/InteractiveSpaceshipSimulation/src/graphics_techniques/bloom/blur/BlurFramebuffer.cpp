#include "../../../../headers/graphics_techniques/bloom/blur/BlurFramebuffer.h"

BlurFramebuffer::BlurFramebuffer(unsigned int windowWidth, unsigned int windowHeight):
    FBOs(), colorBuffers()
{
    glGenFramebuffers(2, FBOs);

    glGenTextures(2, colorBuffers);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBOs[i]);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffers[i], 0
        );
        checkIfFramebufferComplete();
    }
}

void BlurFramebuffer::checkIfFramebufferComplete()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
}
