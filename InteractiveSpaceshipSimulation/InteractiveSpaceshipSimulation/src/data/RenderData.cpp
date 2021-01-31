#include "data/RenderData.h"

RenderData::RenderData(ModelData& modelData): renderContext(), simplifiedRenderContext(), modelData(modelData)
{
	obj::Model model = modelData.getModel();
	renderContext.initFromOBJ(model);
	obj::Model simplifiedModel = modelData.getSimplifiedModel();
	simplifiedRenderContext.initFromOBJ(simplifiedModel);
}

Core::RenderContext& RenderData::getRenderContext()
{
	return renderContext;
}

Core::RenderContext& RenderData::getSimplifiedRenderContext()
{
	return simplifiedRenderContext;
}

const ModelData& RenderData::getModelData()
{
	return modelData;
}
