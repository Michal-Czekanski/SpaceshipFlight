#include "data/RenderData.h"

RenderData::RenderData(ModelData& modelData): renderContext(), simplifiedRenderContext(), modelData(modelData)
{
	obj::Model model = modelData.getModel();
	renderContext.initFromOBJ(model);
	obj::Model simplifiedModel = modelData.getSimplifiedModel();
	simplifiedRenderContext.initFromOBJ(simplifiedModel);
}

Core::RenderContext RenderData::getRenderContext() const
{
	return renderContext;
}

Core::RenderContext RenderData::getSimplifiedRenderContext() const
{
	return simplifiedRenderContext;
}

const ModelData& RenderData::getModelData() const
{
	return modelData;
}
