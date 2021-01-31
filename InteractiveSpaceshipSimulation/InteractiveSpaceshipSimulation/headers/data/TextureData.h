#pragma once

#include "glew.h"
#include "freeglut.h"

class TextureData
{
public:
	TextureData(GLuint texture, GLuint textureNormal);
	
	GLuint getTexture();
	GLuint getTextureNormal();

private:
	GLuint texture;
	GLuint textureNormal;
};

