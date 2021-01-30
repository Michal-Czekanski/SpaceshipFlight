#include "utils/Time.h"

long long Time::measureStart;
long long Time::lastFrameTime;
long long Time::currentFrameTime;
long long Time::deltaTime;
float Time::deltaTimeSec;
long long Time::gameDuration;
bool Time::isRunning;

void Time::start()
{
	if (!isRunning)
	{
		Time::isRunning = true;
		Time::measureStart = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
		Time::lastFrameTime = 0;
		Time::currentFrameTime = 0;
		Time::deltaTime = 0;
		Time::gameDuration = 0;
		PerformanceMeasure::start();
	}
}

void Time::update()
{
	if (isRunning)
	{
		Time::lastFrameTime = currentFrameTime;
		Time::currentFrameTime = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - measureStart;
		Time::deltaTime = currentFrameTime - lastFrameTime;
		Time::deltaTimeSec = Time::deltaTime / 1000.0f;
		Time::gameDuration += Time::deltaTime;
		PerformanceMeasure::updatePerformanceMeasures(Time::deltaTimeSec);
	}
}

long long Time::getDeltaTime()
{
	return Time::deltaTime;
}

float Time::getDeltaTimeSec()
{
	return Time::deltaTimeSec;
}

long long Time::getGameDuration()
{
	return Time::gameDuration;
}

