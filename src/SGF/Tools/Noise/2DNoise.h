#pragma once

#include "Utilities/Math.h"
#include "Namespace.h"

SGF_NAMESPACE(::Tools)
	
SGF_DECIMAL Noise2(int x, int y, unsigned int i);
SGF_DECIMAL SmoothNoise2(int x, int y, unsigned int noiseIndex = 1, unsigned int samples = 1);
SGF_DECIMAL LinearSmoothNoise2(double x, double y, unsigned int noiseIndex = 1);
SGF_DECIMAL CosineSmoothNoise2(double x, double y, unsigned int noiseIndex = 1);
SGF_DECIMAL CubicSmoothNoise2(double x, double y, unsigned int noiseIndex = 1);
	
END_NAMESPACE