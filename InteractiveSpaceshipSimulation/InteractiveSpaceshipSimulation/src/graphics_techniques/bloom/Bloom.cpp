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
	GLuint blurredBrightLightsTexture = blur.blur(screenQuad, hdrFramebuffer.getBrightLightsTexture());

	GLuint sceneTexture = hdrFramebuffer.getSceneTexture();
	bloomBlend(sceneTexture, blurredBrightLightsTexture);
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
