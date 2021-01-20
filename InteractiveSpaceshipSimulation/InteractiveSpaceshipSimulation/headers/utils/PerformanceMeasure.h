#pragma once

#include "../Time.h"
#include <vector>

class PerformanceMeasure
{
private:
	/// <summary>
	/// Miliseconds per frame - better way of measuring performance than FPS.
	/// </summary>
	static float msPerFrame;

	static int framesPerSecond;

	static int framesCounter;

	/// <summary>
	/// Timer used to measure performance.
	/// </summary>
	static float timer;

	/// <summary>
	/// How much time performance measuring should take in seconds.
	/// </summary>
	static const float measureTime;

	/// <summary>
	/// Resets timer and measures. Should be called every second.
	/// </summary>
	static void reset();

	static bool isRunning;

	static void takeMeasures(int framesCount);

	static std::vector<void(*)()> measuresTakenListeners;

	static void callListeners();

public:
	/// <summary>
	/// Returns miliseconds needed to render frame. Good performance measure.
	/// </summary>
	static float getMsPerFrame();

	/// <summary>
	/// Updates performance measures like framesCounter.
	/// </summary>
	/// <returns></returns>
	static void updatePerformanceMeasures(float deltaTime);

	/// <summary>
	/// Returns Frame Per Second. Bad performance measure.
	/// </summary>
	/// <returns></returns>
	static int getFPS();

	/// <summary>
	/// Stars measuring performance.
	/// </summary>
	static void start();

	static void addMeasuresTakenListener(void(*measuresTakenListener)());

	static void removeMeasuresTakenListener(void(*measuresTakenListener)());
};

