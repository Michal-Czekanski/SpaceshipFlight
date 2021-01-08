#include "../../headers/utils/Calculations.h"

glm::quat calculateRotationQuat(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ)
{
	glm::quat quatX = glm::angleAxis(rotationAngleX, glm::vec3(1, 0, 0));
	glm::quat quatY = glm::angleAxis(rotationAngleY, glm::vec3(0, 1, 0));
	glm::quat quatZ = glm::angleAxis(rotationAngleZ, glm::vec3(0, 0, 1));

	glm::quat rotationChange = quatZ * quatY * quatX;

	return glm::normalize(rotationChange * initRotationQuat);
}