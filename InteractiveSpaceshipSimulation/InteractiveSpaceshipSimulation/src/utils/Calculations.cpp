#include "../../headers/utils/Calculations.h"

glm::quat calculateRotationQuatWorldAxises(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ)
{
	glm::quat quatX = glm::angleAxis(rotationAngleX, glm::vec3(1, 0, 0));
	glm::quat quatY = glm::angleAxis(rotationAngleY, glm::vec3(0, 1, 0));
	glm::quat quatZ = glm::angleAxis(rotationAngleZ, glm::vec3(0, 0, 1));

	glm::quat rotationChange = quatZ * quatY * quatX;

	return glm::normalize(rotationChange * initRotationQuat);
}

glm::quat calculateRotationQuatLocalAxises(glm::quat initRotationQuat, glm::vec3 localXAxis, glm::vec3 localYAxis, glm::vec3 localZAxis, float rotationAngleX, float rotationAngleY, float rotationAngleZ)
{
	glm::quat quatX = glm::angleAxis(rotationAngleX, localXAxis);
	glm::quat quatY = glm::angleAxis(rotationAngleY, localYAxis);
	glm::quat quatZ = glm::angleAxis(rotationAngleZ, localZAxis);

	glm::quat rotationChange = quatZ * quatY * quatX;
	return glm::normalize(rotationChange * initRotationQuat);
}

glm::quat rotateV1ToV2(glm::vec3 v1, glm::vec3 v2)
{
	glm::quat q;

	float dot = glm::dot(v1, v2);
	if (dot > 0.999999)
	{
		// Pararell vectors -> return identity quat.
		return q;
	}
	if (dot < -0.999999) 
	{
		// Opposite vectors -> return 180 degree rotation.
		return glm::angleAxis(glm::radians(180.0f), glm::vec3(0, 1, 0));
	}

	glm::vec3 a = glm::cross(v1, v2);
	q.x = a.x; q.y = a.y; q.z = a.z; // q.xyz = a
	q.w = sqrt((pow(v1.length(), 2)) * (pow(v2.length(), 2))) + dot;
	return glm::normalize(q);
}

float randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

glm::quat randomRotationQuat()
{
	glm::vec3 axis = glm::ballRand(1.0f);
	float angle = randomFloat(glm::radians(0.0f), glm::radians(360.0f));
	return glm::angleAxis(angle, axis);
}

int randomInt(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range

	return distr(gen);
}
