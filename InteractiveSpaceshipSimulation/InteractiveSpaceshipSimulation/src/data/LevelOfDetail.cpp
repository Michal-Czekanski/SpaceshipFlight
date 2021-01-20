#include "../../headers/data/LevelOfDetail.h"

LevelOfDetail::LevelOfDetail(float distanceFromCamera)
{
	if (distanceFromCamera <= highDetailMaxDistance)
	{
		detailLevel = LevelOfDetailEnum::High;
	}
	else
	{
		detailLevel = LevelOfDetailEnum::Low;
	}
}

LevelOfDetailEnum LevelOfDetail::getDetailLevel()
{
	return detailLevel;
}
