#include "2DNoise.h"

#include "Utilities/Math.h"

SGF_NAMESPACE(::Tools)
/*
 * Random number generator
 * uses a set of prime numbers as a seed
 * in order to get a different looking noise.
 * can be swapped with mt19937
 */
SGF_DECIMAL Noise2(const int x, const int y, const unsigned int i)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int a = PRIME_NUMS[i][0], b = PRIME_NUMS[i][1], c = PRIME_NUMS[i][2];
	return (1.0 - ((n * (n * n * a + b) + c) & 0x7fffffff) / 1073741824.0);
}

SGF_DECIMAL SmoothNoise2(const int x, const int y, const unsigned int noiseIndex, const unsigned int samples)
{
	unsigned k = 4;
	SGF_DECIMAL total = Noise2(x, y, noiseIndex) / k;

	for (unsigned int i = 1; i <= samples; i++)
	{
		k <<= 1;
	
		// Sides
		total +=
			(
				Noise2(x + i, y, noiseIndex) +
				Noise2(x - i, y, noiseIndex) +
				Noise2(x, y + i, noiseIndex) +
				Noise2(x, y - i, noiseIndex)
				) / k;

		k <<= 1;
		
		// Corners
		total += 
			(	Noise2(x - i, y - i, noiseIndex) +
				Noise2(x + i, y - i, noiseIndex) +
				Noise2(x - i, y + i, noiseIndex) +
				Noise2(x + i, y + i, noiseIndex)
			) / k;
	}

	return total;
}

SGF_DECIMAL LinearSmoothNoise2(const double x, const double y, const unsigned int noiseIndex)
{
	const int intX = (int)x;
	const SGF_DECIMAL  fracX = x - intX;
	const int intY = (int)y;
	const SGF_DECIMAL fracY = y - intY;

	SGF_DECIMAL v0 = SmoothNoise2(x, y, noiseIndex);
	SGF_DECIMAL v1 = SmoothNoise2(x + 1, y, noiseIndex);

	SGF_DECIMAL v2 = SmoothNoise2(x, y + 1, noiseIndex);
	SGF_DECIMAL v3 = SmoothNoise2(x + 1, y + 1, noiseIndex);

	SGF_DECIMAL y1 = LinearInterpolate(v0, v1, fracX);
	SGF_DECIMAL y2 = LinearInterpolate(v2, v3, fracX);

	return LinearInterpolate(y1, y2, fracY);
}

SGF_DECIMAL CosineSmoothNoise2(const double x, const double y, const unsigned int noiseIndex)
{
	const int intX = (int)x;
	const SGF_DECIMAL fracX = x - intX;

	const int intY = (int)y;
	const SGF_DECIMAL fracY = y - intY;

	SGF_DECIMAL v0 = SmoothNoise2(x, y, noiseIndex);
	SGF_DECIMAL v1 = SmoothNoise2(x + 1, y, noiseIndex);

	SGF_DECIMAL v2 = SmoothNoise2(x, y + 1, noiseIndex);
	SGF_DECIMAL v3 = SmoothNoise2(x + 1, y + 1, noiseIndex);

	SGF_DECIMAL y1 = CosineInterpolate(v0, v1, fracX);
	SGF_DECIMAL y2 = CosineInterpolate(v2, v3, fracX);

	return CosineInterpolate(y1, y2, fracY);
}

SGF_DECIMAL CubicSmoothNoise2(const double x, const double y, const unsigned int noiseIndex)
{
	const int intX = (int)x;
	const SGF_DECIMAL fracX = x - intX;

	const int intY = (int)y;
	const SGF_DECIMAL fracY = y - intY;

	// Before A
	SGF_DECIMAL a00 = SmoothNoise2(x - 1, y - 1, noiseIndex);
	SGF_DECIMAL a01 = SmoothNoise2(x, y - 1, noiseIndex);
	SGF_DECIMAL a02 = SmoothNoise2(x + 1, y - 1, noiseIndex);
	SGF_DECIMAL a03 = SmoothNoise2(x + 2, y - 1, noiseIndex);

	// A
	SGF_DECIMAL v00 = SmoothNoise2(x - 1, y, noiseIndex);
	SGF_DECIMAL v01 = SmoothNoise2(x, y, noiseIndex);
	SGF_DECIMAL v02 = SmoothNoise2(x + 1, y, noiseIndex);
	SGF_DECIMAL v03 = SmoothNoise2(x + 2, y, noiseIndex);
	
	// B
	SGF_DECIMAL v10 = SmoothNoise2(x - 1, y + 1, noiseIndex);
	SGF_DECIMAL v11 = SmoothNoise2(x, y + 1, noiseIndex);
	SGF_DECIMAL v12 = SmoothNoise2(x + 1, y + 1, noiseIndex);
	SGF_DECIMAL v13 = SmoothNoise2(x + 2, y + 1, noiseIndex);

	// After B
	SGF_DECIMAL b00 = SmoothNoise2(x - 1, y + 2, noiseIndex);
	SGF_DECIMAL b01 = SmoothNoise2(x, y + 2, noiseIndex);
	SGF_DECIMAL b02 = SmoothNoise2(x + 1, y + 2, noiseIndex);
	SGF_DECIMAL b03 = SmoothNoise2(x + 2, y + 2, noiseIndex);

	SGF_DECIMAL y0 = CubicInterpolate(a00, a01, a02, a03, fracX);
	SGF_DECIMAL y1 = CubicInterpolate(v00, v01, v02, v03, fracX);
	SGF_DECIMAL y2 = CubicInterpolate(v10, v11, v12, v13, fracX);
	SGF_DECIMAL y3 = CubicInterpolate(b00, b01, b02, b03, fracX);

	return CubicInterpolate(y0, y1, y2, y3, fracY);
}

END_NAMESPACE
	