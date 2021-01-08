#pragma once

#include "glm.hpp"
#include "ext.hpp"

glm::quat calculateRotationQuat(glm::quat initRotationQuat, float rotationAngleX, float rotationAngleY, float rotationAngleZ);