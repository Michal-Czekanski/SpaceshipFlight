#pragma once

#include "data/TextureData.h"
#include <vector>
#include "utils/Texture.h"
#include <string>

/// <summary>
/// Textures container - when created loads all textures.
/// </summary>
class Textures
{
public:
	/// <summary>
	/// Textures container - when created loads all textures.
	/// </summary>
	Textures(unsigned int starsTexturesNum, unsigned int asteroidsTexturesNum, 
		unsigned int planetsTexturesNum, unsigned int moonsTexturesNum);

	TextureData& getShipTextureData();
	std::vector<TextureData>& getAsteroidTexturesDatas();
	std::vector<TextureData>& getStarsTexturesDatas();
	std::vector<TextureData>& getPlanetsTexturesDatas();
	std::vector<TextureData>& getMoonsTexturesDatas();
	TextureData& getSmokeTextureData();

	unsigned int getStarsTexturesNum();
	unsigned int getPlanetsTexturesNum();
	unsigned int getAsteroidsTexturesNum();
	unsigned int getMoonsTexturesNum();

private:
	TextureData shipTextureData;

	unsigned int starsTexturesNum;
	std::vector<TextureData> starsTexturesDatas;
	
	unsigned int asteroidsTexturesNum;
	std::vector<TextureData> asteroidsTexturesDatas;
	
	unsigned int planetsTexturesNum;
	std::vector<TextureData> planetsTexturesDatas;
	
	unsigned int moonsTexturesNum;
	std::vector<TextureData> moonsTexturesDatas;

	TextureData smokeTextureData;

	void loadPlanetsTextures(std::string dirName, unsigned int texturesNum);
	void loadAsteroidsTextures(std::string dirName, unsigned int texturesNum);
	void loadStarsTextures(std::string dirName, unsigned int texturesNum);
	void loadShipTextures();
	void loadMoonsTextures(std::string dirName, unsigned int texturesNum);
	void loadSmokeTexture();

};

