#pragma once
#include "Utilities/Math.h"
#include "Namespace.h"

SGF_NAMESPACE(::Tools)
	
SGF_DECIMAL Noise1(int x, unsigned i);
SGF_DECIMAL SmoothNoise1(double x, unsigned noiseIndex = 1, unsigned samples = 1);
SGF_DECIMAL LinearSmoothNoise1(double x, unsigned noiseIndex = 1);
SGF_DECIMAL CosineSmoothNoise1(double x, unsigned noiseIndex = 1);
SGF_DECIMAL CubicSmoothNoise1(double x, unsigned noiseIndex = 1);
	
END_NAMESPACE
