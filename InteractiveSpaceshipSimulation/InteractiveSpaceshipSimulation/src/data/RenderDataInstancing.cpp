#include "data/RenderDataInstancing.h"

RenderDataInstancing::RenderDataInstancing(ModelData& modelData):
	RenderData(modelData)
{
	renderContext.initInstanceBuffer();
	simplifiedRenderContext.initInstanceBuffer();
}