#include "../../../../headers/graphics_techniques/bloom/blur/Blur.h"

Blur::Blur(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur):
	blurAmount(10), programBlur(programBlur), framebuffer(windowWidth, windowHeight)
{
}
