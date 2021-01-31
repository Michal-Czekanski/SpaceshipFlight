#include "data/TextureData.h"

TextureData::TextureData(GLuint texture, GLuint textureNormal):
	texture(texture), textureNormal(textureNormal)
{
}

GLuint TextureData::getTexture()
{
	return texture;
}

GLuint TextureData::getTextureNormal()
{
	return textureNormal;
}
