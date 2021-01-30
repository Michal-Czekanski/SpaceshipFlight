#include "objectsInSpace/renderables/orbitables/Planet.h"

Planet::Planet(glm::vec3 position, ModelData& modelData, glm::vec3 scale, GLuint programDraw, GLuint texture, GLuint textureNormals):
	Orbitable(position, modelData, scale, NULL, glm::vec3(), 0.0f, programDraw, texture, textureNormals)
{
}

Planet::Planet(glm::vec3 position, ModelData &modelData, glm::vec3 scale, 
	Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw, GLuint texture, GLuint textureNormals):
	Orbitable(position, modelData, scale, orbitAround, orbitPlaneVec2, orbitSpeed, programDraw, texture, textureNormals)
{
	this->orbitAround = orbitAround;
}

void Planet::update()
{
	if (this->orbitAround)
	{
		orbit();
	}
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}

Star* Planet::getOrbitCenter()
{
	return this->orbitAround;
}

