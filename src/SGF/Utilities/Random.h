#pragma once

#include <random>
#include "Namespace.h"

SGF_NAMESPACE(::Util)

class Random
{
public:
	Random();
	Random(unsigned int seed);
	static Random& get();
	static void init();

	template<int a, int b>
	int Int()
	{
		std::uniform_int_distribution<int> dist(a, b);
		return dist(m_Engine);
	}

	float Float(float a, float b)
	{
		std::uniform_real_distribution<float> dist(a, b);
		return dist(m_Engine);
	}

	double Double(double a, double b)
	{
		std::uniform_real_distribution<double> dist(a, b); 
		return dist(m_Engine);
	}

private:
	std::mt19937 m_Engine;
	static Random s_Ran;
	void setupStatic();
};

END_NAMESPACE


