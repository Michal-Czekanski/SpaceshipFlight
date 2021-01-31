#pragma once

#include "utils//Render_Utils.h"
#include "data/ModelData.h"

class RenderData
{
public:
	RenderData(ModelData& modelData);
	Core::RenderContext getRenderContext() const;
	Core::RenderContext getSimplifiedRenderContext() const;
	const ModelData& getModelData() const;
protected:
	Core::RenderContext renderContext;
	Core::RenderContext simplifiedRenderContext;
	const ModelData modelData;
};

