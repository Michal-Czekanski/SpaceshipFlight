#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include <random>

/// <summary>
/// Calculates rotation quat using world space axises.
/// </summary>
/// <param name="initRotationQuat"></param>
/// <param name="rotationAngleX"></param>
/// <param name="rotationAngleY"></param>
/// <param name="rotationAngleZ"></param>
/// <returns></returns>
glm::quat calculateRotationQuatWorldAxises(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ);

/// <summary>
/// Calculates rotaion quat using given local axises.
/// </summary>
/// <param name="initRotationQuat"></param>
/// <param name="localXAxis"></param>
/// <param name="localYAxis"></param>
/// <param name="localZAxis"></param>
/// <param name="rotationAngleX"></param>
/// <param name="rotationAngleY"></param>
/// <param name="rotationAngleZ"></param>
/// <returns></returns>
glm::quat calculateRotationQuatLocalAxises(glm::quat initRotationQuat, glm::vec3 localXAxis, glm::vec3 localYAxis, glm::vec3 localZAxis, float rotationAngleX, float rotationAngleY, float rotationAngleZ);


/// <summary>
/// Calculates quaternion representing rotation from v1 to v2.
/// </summary>
/// <param name="v1">First vector.</param>
/// <param name="v2">Second vector.</param>
/// <returns>Quaternion representing rotation from v1 to v2.</returns>
glm::quat rotateV1ToV2(glm::vec3 v1, glm::vec3 v2);

/// <summary>
/// Generates random float in range (a, b)
/// </summary>
float randomFloat(float a, float b);

/// <summary>
/// Generates random rotation quaternion.
/// </summary>
glm::quat randomRotationQuat();

/// <summary>
/// Generates random integer in range [min, max]
/// </summary>
int randomInt(int min, int max);