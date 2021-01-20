#pragma once
enum class LevelOfDetailEnum
{
	Low, High
};

class LevelOfDetail
{
private:
	LevelOfDetailEnum detailLevel;
	const int highDetailMaxDistance = 150.0f;

public:
	LevelOfDetail(float distanceFromCamera);
	LevelOfDetailEnum getDetailLevel();
};

