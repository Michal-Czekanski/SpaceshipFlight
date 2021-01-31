#include "data/Textures.h"

Textures::Textures() : shipTextureData(0, 0)
{
	loadShipTextures();
	loadStarsTextures("textures/stars", 3);
	loadPlanetsTextures("textures/planets", 10);
	loadAsteroidsTextures("textures/asteroids", 2);
	loadMoonsTextures("textures/moons", 4);
}

TextureData& Textures::getShipTextureData()
{
	return shipTextureData;
}

std::vector<TextureData>& Textures::getAsteroidTexturesDatas()
{
	return asteroidsTexturesDatas;
}

std::vector<TextureData>& Textures::getStarsTexturesDatas()
{
	return starsTexturesDatas;
}

std::vector<TextureData>& Textures::getPlanetsTexturesDatas()
{
	return planetsTexturesDatas;
}

std::vector<TextureData>& Textures::getMoonsTexturesDatas()
{
	return moonsTexturesDatas;
}

void Textures::loadPlanetsTextures(std::string dirName, unsigned int texturesNum)
{
	for (unsigned int i = 1; i <= texturesNum; i++)
	{
		const std::string textureFilename = dirName + "planet" + std::to_string(i) + "_texture.png";
		const std::string textureNormalFilename = dirName + "planet" + std::to_string(i) + "_texture_normal.png";
		planetsTexturesDatas.emplace_back(Core::LoadTexture(textureFilename.c_str()), Core::LoadTexture(textureNormalFilename.c_str()));
	}
}

void Textures::loadAsteroidsTextures(std::string dirName, unsigned int texturesNum)
{
	for (unsigned int i = 1; i <= texturesNum; i++)
	{
		const std::string textureFilename = dirName + "asteroid" + std::to_string(i) + "_texture.png";
		const std::string textureNormalFilename = dirName + "asteroid" + std::to_string(i) + "_texture_normal.png";
		asteroidsTexturesDatas.emplace_back(Core::LoadTexture(textureFilename.c_str()), Core::LoadTexture(textureNormalFilename.c_str()));
	}
}

void Textures::loadStarsTextures(std::string dirName, unsigned int texturesNum)
{
	for (unsigned int i = 1; i <= texturesNum; i++)
	{
		const std::string textureFilename = dirName + "star" + std::to_string(i) + "_texture.png";
		starsTexturesDatas.emplace_back(Core::LoadTexture(textureFilename.c_str()), 0);
	}
}

void Textures::loadShipTextures()
{
	GLuint shipTexture = Core::LoadTexture("textures/spaceship/spaceship_model_texture.png");
	GLuint shipTextureNormal = Core::LoadTexture("textures/spaceship/spaceship_model_normal.png");
	shipTextureData = TextureData(shipTexture, shipTextureNormal);
}

void Textures::loadMoonsTextures(std::string dirName, unsigned int texturesNum)
{
	for (unsigned int i = 1; i <= texturesNum; i++)
	{
		const std::string textureFilename = dirName + "moon" + std::to_string(i) + "_texture.png";
		const std::string textureNormalFilename = dirName + "moon" + std::to_string(i) + "_texture_normal.png";
		moonsTexturesDatas.emplace_back(Core::LoadTexture(textureFilename.c_str()), Core::LoadTexture(textureNormalFilename.c_str()));
	}
}
