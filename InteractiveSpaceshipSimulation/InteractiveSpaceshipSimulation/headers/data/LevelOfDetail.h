#pragma once
enum class LevelOfDetailEnum
{
	Low, High
};

class LevelOfDetail
{
private:
	LevelOfDetailEnum detailLevel;
	const float highDetailMaxDistance = 200.0f;

public:
	LevelOfDetail(float distanceFromCamera);
	LevelOfDetailEnum getDetailLevel();
};

