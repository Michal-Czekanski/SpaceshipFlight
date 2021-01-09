#include "../headers/Moon.h"

Moon::Moon(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, 
	glm::vec3 forwardInModelSpace, glm::vec3 scale, Planet* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed):
	Orbitable(position, rotationQuat, vectorForward, vectorTop, model, topInModelSpace, forwardInModelSpace, scale, orbitAround, orbitPlaneVec2, orbitSpeed)
{
}
