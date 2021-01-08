#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "CameraAttachable.h"
#include "utils/Camera.h"
#include "utils/Calculations.h"

class AttachableCamera
{
private:
	/// <summary>
	/// Specifies how far behind ship camera should be placed.
	/// </summary>
	float camOffsetMultiplier;

	/// <summary>
	/// Specifies if camera should be above, below or at the ship level.
	/// </summary>
	float upOffsetMultiplier;

	glm::vec3 calculateCamOffset();

	glm::mat4 cameraMatrix;

	CameraAttachable* attachedObject;

	glm::quat initCameraRotation;

	const glm::vec3 initCameraLookDir = glm::vec3(0, 0, -1);
public:
	AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier);
	AttachableCamera(float camOffsetMultiplier, float upOffsetMultiplier, CameraAttachable* attachedObject);
	
	/// <summary>
	/// Updates camera matrix based on attached object's position and rotation.
	/// </summary>
	/// <returns>Updated camera matrix.</returns>
	glm::mat4 updateCameraMatrix();

	/// <summary>
	/// </summary>
	/// <returns>Camera matrix.</returns>
	glm::mat4 getCameraMatrix();
};

