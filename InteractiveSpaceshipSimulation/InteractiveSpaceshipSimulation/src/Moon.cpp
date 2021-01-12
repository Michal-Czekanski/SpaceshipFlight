#include "../headers/Moon.h"

Moon::Moon(glm::vec3 position, ModelData &modelData,
	glm::vec3 scale, Planet* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed):
	Orbitable(position, modelData, scale, orbitAround, orbitPlaneVec2, orbitSpeed)
{
}
