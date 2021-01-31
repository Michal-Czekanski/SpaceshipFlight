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
	Textures();

	TextureData& getShipTextureData();
	std::vector<TextureData>& getAsteroidTexturesDatas();
	std::vector<TextureData>& getStarsTexturesDatas();
	std::vector<TextureData>& getPlanetsTexturesDatas();
	std::vector<TextureData>& getMoonsTexturesDatas();

private:
	TextureData shipTextureData;
	std::vector<TextureData> starsTexturesDatas;
	std::vector<TextureData> asteroidsTexturesDatas;
	std::vector<TextureData> planetsTexturesDatas;
	std::vector<TextureData> moonsTexturesDatas;

	void loadPlanetsTextures(std::string dirName, unsigned int texturesNum);
	void loadAsteroidsTextures(std::string dirName, unsigned int texturesNum);
	void loadStarsTextures(std::string dirName, unsigned int texturesNum);
	void loadShipTextures();
	void loadMoonsTextures(std::string dirName, unsigned int texturesNum);

};

