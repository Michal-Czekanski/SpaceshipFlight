#include "../../headers/utils/PerformanceMeasure.h"

float PerformanceMeasure::msPerFrame;
int PerformanceMeasure::framesPerSecond;
int PerformanceMeasure::framesCounter;
float PerformanceMeasure::timer;
const float PerformanceMeasure::measureTime = 1.0f;
bool PerformanceMeasure::isRunning;
std::vector<void (*)()> PerformanceMeasure::measuresTakenListeners;

void PerformanceMeasure::updatePerformanceMeasures(float deltaTime)
{
	if (PerformanceMeasure::isRunning)
	{
		PerformanceMeasure::timer -= deltaTime;
		if (PerformanceMeasure::timer <= 0.0f)
		{
			PerformanceMeasure::takeMeasures(PerformanceMeasure::framesCounter);
			PerformanceMeasure::reset();
		}
		PerformanceMeasure::framesCounter++;
	}
}

void PerformanceMeasure::takeMeasures(int framesCount)
{
	PerformanceMeasure::framesPerSecond = framesCount;
	PerformanceMeasure::msPerFrame = 1000.0f / framesCount;
	PerformanceMeasure::callListeners();
}

void PerformanceMeasure::callListeners()
{
	for (void(*listener)() : PerformanceMeasure::measuresTakenListeners)
	{
		listener();
	}
}

void PerformanceMeasure::reset()
{
	PerformanceMeasure::timer = PerformanceMeasure::measureTime;
	PerformanceMeasure::framesCounter = 0;
}

float PerformanceMeasure::getMsPerFrame()
{
	return PerformanceMeasure::msPerFrame;
}

int PerformanceMeasure::getFPS()
{
	return PerformanceMeasure::framesPerSecond;
}

void PerformanceMeasure::start()
{
	if (!isRunning)
	{
		PerformanceMeasure::msPerFrame = 0.0f;
		PerformanceMeasure::framesCounter = 0;
		PerformanceMeasure::framesPerSecond = 0;
		PerformanceMeasure::isRunning = true;
		PerformanceMeasure::timer = PerformanceMeasure::measureTime;
	}
}

void PerformanceMeasure::addMeasuresTakenListener(void(*measuresTakenListener)())
{
	PerformanceMeasure::measuresTakenListeners.push_back(measuresTakenListener);
}

void PerformanceMeasure::removeMeasuresTakenListener(void(*measuresTakenListener)())
{
	auto begin = PerformanceMeasure::measuresTakenListeners.begin();
	auto end = PerformanceMeasure::measuresTakenListeners.end();
	PerformanceMeasure::measuresTakenListeners.erase(std::remove(begin, end, measuresTakenListener), end);
}
