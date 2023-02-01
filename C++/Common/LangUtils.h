#pragma once
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <Windows.h>

static class Math
{
public:
	inline
	static double Clamp(double value, double min, double max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	inline
	static double Sqrt(double value)
	{
		return sqrt(value);
	}

	inline
	static double Sin(double value)
	{
		return sin(value);
	}

	inline
	static double Floor(double value)
	{
		return floor(value);
	}

	inline
	static double Pow(double value, double x)
	{
		return pow(value, x);
	}

	inline
	static double Max(double value, double x)
	{
		return fmax(value, x);
	}

	inline
	static double Min(double value, double x)
	{
		return fmin(value, x);
	}

	inline
	static double Abs(double value)
	{
		return abs(value);
	}

	inline
	static double MaxValue()
	{
		return DBL_MAX;
	}
};

static class MathF
{
public:
	inline
	static float Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	inline
	static float Sqrt(float value)
	{
		return sqrt(value);
	}

	inline
	static float Pow(float value, float x)
	{
		return pow(value, x);
	}

	inline
	static float Max(float value, float x)
	{
		return fmax(value, x);
	}

	inline
	static float Min(float value, float x)
	{
		return fmin(value, x);
	}

	inline
	static float Abs(float value)
	{
		return abs(value);
	}

	inline
	static float MaxValue()
	{
		return FLT_MAX;
	}
};

static class Environment
{
public:
	static int ProcessorCount()
	{
		return std::thread::hardware_concurrency();
	}
};

//class Thread
//{
//public:
//	std::thread* thread;
//
//	Thread(std::_Fn&& _Fx)
//	{
//		thread = new std::thread(_Fx);
//	}
//};

//class ManualResetEvent
//{
//public:
//	bool signalled;
//	pthread_mutex_t mutex;
//	pthread_cond_t cond;
//};