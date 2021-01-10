#include "../headers/Time.h"

long long Time::measureStart;
long long Time::lastFrameTime;
long long Time::currentFrameTime;
long long Time::deltaTime;
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
	}
}

void Time::update()
{
	if (isRunning)
	{
		Time::lastFrameTime = currentFrameTime;
		Time::currentFrameTime = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
		Time::deltaTime = currentFrameTime - lastFrameTime;
		Time::gameDuration += Time::deltaTime;
	}
}

long long Time::getDeltaTime()
{
	return Time::deltaTime;
}

float Time::getDeltaTimeSec()
{
	return Time::deltaTime / 1000.0f;
}

long long Time::getGameDuration()
{
	return Time::gameDuration;
}

