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
