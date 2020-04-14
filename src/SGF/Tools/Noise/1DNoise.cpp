#include "1DNoise.h"

#include "Utilities/Math.h"

SGF_NAMESPACE(::Tools)

inline SGF_DECIMAL Noise1(int x, const unsigned i)
{
	x = (x << 13) ^ x;
	const int a = PRIME_NUMS[i][0], b = PRIME_NUMS[i][1], c = PRIME_NUMS[i][2];
	return (1.0 - ((x * (x * x * a + b) + c) & 0x7fffffff) / 1073741824.0);
}

SGF_DECIMAL SmoothNoise1(const double x, const unsigned noiseIndex, const unsigned samples)
{
	int k = 2;
	SGF_DECIMAL total = Noise1(x, noiseIndex) / k;
	
	for (int i = 1; i <= samples; i++)
	{
		k <<= 1;
		total += Noise1(x - i, noiseIndex) / k + Noise1(x + i, noiseIndex) / k;
	}
	
	return total;
}

SGF_DECIMAL LinearSmoothNoise1(const double x, const unsigned noiseIndex)
{
	const int intX = (int) x;
	const SGF_DECIMAL fraction = x - intX;
	
	const SGF_DECIMAL v0 = SmoothNoise1(intX, noiseIndex);
	const SGF_DECIMAL v1 = SmoothNoise1(intX + 1, noiseIndex);

	return LinearInterpolate(v0, v1, fraction);
}

SGF_DECIMAL CosineSmoothNoise1(const double x, const unsigned noiseIndex)
{
	const int intX = (int) x;
	const SGF_DECIMAL fraction = x - intX;

	const SGF_DECIMAL v0 = SmoothNoise1(intX, noiseIndex);
	const SGF_DECIMAL v1 = SmoothNoise1(intX + 1, noiseIndex);

	return CosineInterpolate(v0, v1, fraction);
}

SGF_DECIMAL CubicSmoothNoise1(const double x, const unsigned noiseIndex)
{
	const int intX = (int) x;
	const SGF_DECIMAL fraction = x - intX;

	const SGF_DECIMAL v0 = SmoothNoise1(intX - 1, noiseIndex);
	const SGF_DECIMAL v1 = SmoothNoise1(intX, noiseIndex);
	const SGF_DECIMAL v2 = SmoothNoise1(intX + 1, noiseIndex);
	const SGF_DECIMAL v3 = SmoothNoise1(intX + 2, noiseIndex);

	return CubicInterpolate(v0, v1, v2, v3, fraction);
}


END_NAMESPACE