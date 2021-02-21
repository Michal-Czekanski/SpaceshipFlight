#include "objectsInSpace/renderables/orbitables/Planet.h"

Planet::Planet(glm::vec3 position, const RenderData& renderData, glm::vec3 scale, GLuint programDraw, TextureData textureData):
	Orbitable(position, renderData, scale, NULL, glm::vec3(), 0.0f, programDraw, textureData)
{
}

Planet::Planet(glm::vec3 position, const RenderData& renderData, glm::vec3 scale,
	Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw, TextureData textureData):
	Orbitable(position, renderData, scale, orbitAround, orbitPlaneVec2, orbitSpeed, programDraw, textureData)
{
	this->orbitAround = orbitAround;
}

Star* Planet::getOrbitCenter()
{
	return this->orbitAround;
}

