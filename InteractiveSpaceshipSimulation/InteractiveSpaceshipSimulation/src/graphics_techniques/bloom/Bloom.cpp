#include "../../../headers/graphics_techniques/bloom/Bloom.h"

Bloom::Bloom(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend)
	: exposure(1.9f), gamma(1.0f), programBloomFinalBlend(programBloomFinalBlend), screenQuad(), 
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
	GLuint blurredBrightLightsTexture = blur.blur(screenQuad, hdrFramebuffer.getBrightLightsTexture());

	GLuint sceneTexture = hdrFramebuffer.getSceneTexture();
	bloomBlend(sceneTexture, blurredBrightLightsTexture);
}

void Bloom::setExposure(float exp)
{
	this->exposure = exp;
}

float Bloom::getExposure()
{
	return exposure;
}

void Bloom::setGamma(float gamma)
{
	this->gamma = gamma;
}

float Bloom::getGamma()
{
	return this->gamma;
}

void Bloom::setBlurAmount(int blurAmount)
{
	blur.setBlurAmount(blurAmount);
}

int Bloom::getBlurAmount()
{
	return blur.getBlurAmount();
}

void Bloom::bloomBlend(GLuint sceneTexture, GLuint blurredBrightLightsTexture)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programBloomFinalBlend);

    Core::SetActiveTexture(sceneTexture, "scene", programBloomFinalBlend, 0);

    Core::SetActiveTexture(blurredBrightLightsTexture, "bloomBlur", programBloomFinalBlend, 1);

    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "exposure"), exposure);
    glUniform1f(glGetUniformLocation(programBloomFinalBlend, "gamma"), gamma);
    screenQuad.render();
}
