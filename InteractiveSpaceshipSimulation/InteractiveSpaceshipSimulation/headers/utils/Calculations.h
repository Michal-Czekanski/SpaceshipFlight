#pragma once

#include "glm.hpp"
#include "ext.hpp"


glm::quat calculateRotationQuat(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ);

/// <summary>
/// Calculates quaternion representing rotation from v1 to v2.
/// </summary>
/// <param name="v1">First vector.</param>
/// <param name="v2">Second vector.</param>
/// <returns>Quaternion representing rotation from v1 to v2.</returns>
glm::quat rotateV1ToV2(glm::vec3 v1, glm::vec3 v2);