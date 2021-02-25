#pragma once

#include "glm.hpp"
#include "ext.hpp"

class ICamera
{
public:
	virtual glm::quat getRotation() = 0;
	virtual glm::mat4 getCameraMatrix() = 0;
	virtual glm::vec3 getCamPos() = 0;
};

