#include "data/RenderableUpdateData.h"

RenderableUpdateData::RenderableUpdateData(PxTransform data):
	rotation(PhysxGLMConverter::PxQuatToQuat(data.q)), position(PhysxGLMConverter::PxVec3ToVec3(data.p)),
	modelMatrix(PhysxGLMConverter::PxMat44ToMat4(data))
{
}

glm::quat& RenderableUpdateData::getRotation()
{
	return rotation;
}

glm::vec3& RenderableUpdateData::getPosition()
{
	return position;
}

glm::mat4& RenderableUpdateData::getModelMatrix()
{
	return modelMatrix;
}
