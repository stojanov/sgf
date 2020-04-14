#pragma once

// if you want to use the cmath constants
//#define _USE_MATH_DEFINES
#include <cmath>

// Using doubles
//#define SGF_USE_DOUBLES

#ifdef SGF_USE_DOUBLES
using SGF_DECIMAL = double;
#else
using SGF_DECIMAL = float;
#endif

#ifndef M_PI
constexpr SGF_DECIMAL M_PI = 3.14159265358979323846;
#endif

#ifndef M_1_PI
constexpr SGF_DECIMAL M_1_PI = 1 / M_PI;
#endif

#ifndef M_PI_2
constexpr SGF_DECIMAL M_PI_2 = M_PI / 2;
#endif

constexpr int PRIME_LEN = 11;

constexpr static int PRIME_NUMS[PRIME_LEN][3] = {
	{ 15731, 789221, 1376312589 },
	{ 995615039, 600173719, 701464987 },
	{ 831731269, 162318869, 136250887 },
	{ 174329291, 946737083, 245679977 },
	{ 362489573, 795918041, 350777237 },
	{ 457025711, 880830799, 909678923 },
	{ 787070341, 177340217, 593320781 },
	{ 405493717, 291031019, 391950901 },
	{ 458904767, 676625681, 424452397 },
	{ 531736441, 939683957, 810651871 },
	{ 997169939, 842027887, 423882827 }
};

inline SGF_DECIMAL fastACos(float x)
{
	static constexpr auto a = static_cast<SGF_DECIMAL>(-0.69813170079773212);
	static constexpr auto b = static_cast<SGF_DECIMAL>(0.87266462599716477);
	static constexpr auto c = static_cast<SGF_DECIMAL>(1.5707963267948966);
	return (a * x * x - b)* x + c;
}

template<typename T>
SGF_DECIMAL LinearInterpolate(T a, T b, T x)
{
	return  a * (1 - x) + b * x;
}

template<SGF_DECIMAL(*f)(SGF_DECIMAL), typename T>
SGF_DECIMAL useSmoothLinearInterpolate(T a, T b, T x)
{
	return f(LinearInterpolate(a, b, x));
}

template<typename T>
SGF_DECIMAL CosineInterpolate(T a, T b,T x)
{
	auto ft = x * M_PI;
	auto f = (1 - cos(ft)) * 0.5f;
	return  a * (1 - f) + b * f;
}

template<typename T>
SGF_DECIMAL CubicInterpolate(T v0, T v1, T v2, T v3, T val)
{
	const SGF_DECIMAL P = (v3 - v2) - (v0 - v1);
	const SGF_DECIMAL Q = (v0 - v1) - P;
	const SGF_DECIMAL R = v2 - v0;

	return P * val * val * val + Q * val * val + R * val + v1;
}

template<typename T, typename U>
auto LinearTranslate(T a1, T b1, U a2, U b2, T x)
{
	return a2 + (b2 - a2) * (1.f * (x - a1) / (b1 - a1));
}

template<SGF_DECIMAL (*f)(SGF_DECIMAL), typename T, typename U>
auto useSmoothLinearTranslate(T a1, T b1, U a2, U b2, T x)
{
	return (a2 + (b2 - a2) * f(LinearTranslate(x, a1, b1, 0.0f, 1.0f)));
}

/*
 * Smoothing functions defined by:
 * Range = [0, 1], Domain = [0, 1]
 */

inline SGF_DECIMAL SinSmooth(SGF_DECIMAL t)
{
	return sin(M_PI_2 * t);
}

inline SGF_DECIMAL SinSmooth_2(SGF_DECIMAL t)
{
	return 1 + sin(M_PI_2 * (t - 1));
}

// t^3
inline SGF_DECIMAL CubicSmooth(SGF_DECIMAL t)
{
	return t * t * t;
}

// 1 + (t - 1)^3
inline SGF_DECIMAL CubicSmooth_2(SGF_DECIMAL t)
{
	const float k = t - 1;
	return 1 + k * k * k;
}

// -2t^3 + 3t^2
inline SGF_DECIMAL CubicSmooth_3(SGF_DECIMAL t)
{
	return -2 * t * t * t + 3 * t * t;
}

// 6t^5 - 15x^4 + 10x^3
inline SGF_DECIMAL CubicSmooth_4(SGF_DECIMAL t)
{
	return 6 * (t * t * t * t * t) - 15 * (t * t * t * t) + 10 * (t * t * t);
}

// 1/pi * arcsin(2t - 1) + 14
inline SGF_DECIMAL ACosSmooth(SGF_DECIMAL t)
{
	return -M_1_PI * acos(2 * t - 1) + 1.f;
}

inline SGF_DECIMAL fastACosSmooth(SGF_DECIMAL t)
{
	return -M_1_PI * fastACos(2 * t - 1) + 1.f;
}