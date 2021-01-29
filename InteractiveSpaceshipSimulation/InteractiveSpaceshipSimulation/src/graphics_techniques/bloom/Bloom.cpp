#include "../../../headers/graphics_techniques/bloom/Bloom.h"

Bloom::Bloom(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend)
	: exposure(3.2f), gamma(1.0f), programBloomFinalBlend(programBloomFinalBlend), screenQuad(), 
	blur(windowWidth, windowHeight, programBlur), hdrFramebuffer(windowWidth, windowHeight)
	
{

}

void Bloom::beforeRendering()
{
	hdrFramebuffer.initRenderingToThisFBO();
}

void Bloom::afterRendering()
{
	hdrFramebuffer.endRenderingToThisFBO();
	GLuint brightLightsTexture = hdrFramebuffer.getBrightLightsTexture();
	blur.blur(screenQuad, brightLightsTexture);

	GLuint sceneTexture = hdrFramebuffer.getSceneTexture();
	bloomBlend(sceneTexture, brightLightsTexture);
}

void Bloom::bloomBlend(GLuint sceneTexture, GLuint blurredBrightLightsTexture)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programBloomFinalBlend);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glUniform1i(glGetUniformLocation(programBloomFinalBlend, "scene"), 0);


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, blurredBrightLightsTexture);
    glUniform1i(glGetUniformLocation(programBloomFinalBlend, "bloomBlur"), 1);


    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "exposure"), exposure);
    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "gamma"), gamma);
    screenQuad.render();
}
