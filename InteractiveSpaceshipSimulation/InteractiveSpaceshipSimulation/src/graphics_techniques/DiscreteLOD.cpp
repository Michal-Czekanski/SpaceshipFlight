#include "../../headers/graphics_techniques/DiscreteLOD.h"

obj::Model& DiscreteLOD::whichModelUse(float distanceFromCamera, obj::Model& simplifiedModel, obj::Model& detailedModel)
{
	LevelOfDetail levelOfDetail = LevelOfDetail(distanceFromCamera);
	if (levelOfDetail.getDetailLevel() == LevelOfDetailEnum::High)
	{
		return detailedModel;
	}
	else if (levelOfDetail.getDetailLevel() == LevelOfDetailEnum::Low)
	{
		return simplifiedModel;
	}
}

Core::RenderContext DiscreteLOD::whichContextUse(float distanceFromCamera, Core::RenderContext& simplifiedContext, Core::RenderContext& detailedContext)
{
	LevelOfDetail levelOfDetail = LevelOfDetail(distanceFromCamera);
	if (levelOfDetail.getDetailLevel() == LevelOfDetailEnum::High)
	{
		return detailedContext;
	}
	else if (levelOfDetail.getDetailLevel() == LevelOfDetailEnum::Low)
	{
		return simplifiedContext;
	}
}
