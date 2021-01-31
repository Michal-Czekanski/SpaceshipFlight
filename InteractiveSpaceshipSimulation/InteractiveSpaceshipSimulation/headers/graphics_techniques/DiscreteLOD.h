#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "../utils/objload.h"
#include "../data/LevelOfDetail.h"
#include "../utils/Render_Utils.h"
#include "data/RenderData.h"

/// <summary>
/// Discrete Level Of Detail - based on distance from camera chooses which model to render: simplified or detailed.
/// </summary>
class DiscreteLOD
{
public:
	/// <summary>
	/// Decides which model should be used to render based on distance from camera.
	/// </summary>
	/// <param name="distanceFromCamera"></param>
	/// <param name="simplifiedModel"></param>
	/// <param name="detailedModel"></param>
	/// <returns></returns>
	obj::Model& whichModelUse(float distanceFromCamera, obj::Model& simplifiedModel, obj::Model& detailedModel);

	/// <summary>
	/// Decides which render context should be used to render based on distance from camera.
	/// </summary>
	/// <param name="distanceFromCamera"></param>
	/// <param name="simplifiedContext"></param>
	/// <param name="detailedContext"></param>
	/// <returns></returns>
	Core::RenderContext whichContextUse(float distanceFromCamera, Core::RenderContext& simplifiedContext, 
		Core::RenderContext& detailedContext);

	/// <summary>
	/// Decides which render context should be used to render based on distance from camera.
	/// </summary>
	/// <returns>Chosen render context.</returns>
	Core::RenderContext whichContextUse(float distanceFromCamera, const RenderData* renderData);

	static bool enabled;
};

