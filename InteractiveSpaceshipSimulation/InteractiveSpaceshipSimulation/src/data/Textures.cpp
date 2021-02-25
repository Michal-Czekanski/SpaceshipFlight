#include "data/Textures.h"

Textures::Textures(unsigned int starsTexturesNum, unsigned int asteroidsTexturesNum,
	unsigned int planetsTexturesNum, unsigned int moonsTexturesNum) : shipTextureData(0, 0),
	starsTexturesNum(starsTexturesNum), asteroidsTexturesNum(asteroidsTexturesNum),
	planetsTexturesNum(planetsTexturesNum), moonsTexturesNum(moonsTexturesNum), smokeTextureData(0, 0)
{
	loadShipTextures();
	loadStarsTextures("textures/stars/", starsTexturesNum);
	loadPlanetsTextures("textures/planets/", planetsTexturesNum);
	loadAsteroidsTextures("textures/asteroids/", asteroidsTexturesNum);
	loadMoonsTextures("textures/moons/", moonsTexturesNum);
	loadSmokeTexture();
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

TextureData& Textures::getSmokeTextureData()
{
	return smokeTextureData;
}

unsigned int Textures::getStarsTexturesNum()
{
	return starsTexturesNum;
}

unsigned int Textures::getPlanetsTexturesNum()
{
	return planetsTexturesNum;
}

unsigned int Textures::getAsteroidsTexturesNum()
{
	return asteroidsTexturesNum;
}

unsigned int Textures::getMoonsTexturesNum()
{
	return moonsTexturesNum;
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

void Textures::loadSmokeTexture()
{
	GLuint smokeTexture = Core::LoadTexture("textures/particles/smoke.png");
	smokeTextureData = TextureData(smokeTexture, 0);
}
