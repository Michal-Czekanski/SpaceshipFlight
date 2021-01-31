#pragma once

#include "utils//Render_Utils.h"
#include "data/ModelData.h"

class RenderData
{
public:
	RenderData(ModelData& modelData);
	Core::RenderContext& getRenderContext();
	Core::RenderContext& getSimplifiedRenderContext();
	const ModelData& getModelData();
private:
	Core::RenderContext renderContext;
	Core::RenderContext simplifiedRenderContext;
	const ModelData modelData;
};

