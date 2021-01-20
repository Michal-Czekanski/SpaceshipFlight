#pragma once

#include <chrono>
#include "utils/PerformanceMeasure.h"

using namespace std::chrono;

class Time
{
private:
	/// <summary>
	/// In miliseconds.
	/// </summary>
	static long long measureStart;

	/// <summary>
	/// In miliseconds
	/// </summary>
	static long long lastFrameTime;

	/// <summary>
	/// In miliseconds
	/// </summary>
	static long long currentFrameTime;

	/// <summary>
	/// In miliseconds
	/// </summary>
	static long long deltaTime;


	/// <summary>
	/// Delta time in seconds.
	/// </summary>
	static float deltaTimeSec;

	/// <summary>
	/// In miliseconds
	/// </summary>
	static long long gameDuration;
	static bool isRunning;
public:
	/// <summary>
	/// Starts measuring time.
	/// </summary>
	static void start();

	/// <summary>
	/// Updates time (last and current frame time, delta time).
	/// </summary>
	static void update();

	/// <summary>
	/// Returns time passed since last frame in miliseconds.
	/// </summary>
	/// <returns></returns>
	static long long getDeltaTime();

	/// <summary>
	/// Returns time passed since last frame in seconds.
	/// </summary>
	static float getDeltaTimeSec();

	/// <summary>
	/// Returns game duration in miliseconds
	/// </summary>
	/// <returns></returns>
	static long long getGameDuration();
};

