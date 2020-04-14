#pragma once
#include <SFML/System/Vector2.hpp>
#include "Namespace.h"

SGF_NAMESPACE(::Util)

template<typename T, typename U>
sf::Vector2<T> v2Cast(sf::Vector2<U>& vec)
{
	return sf::Vector2<T>(static_cast<T>(vec.x), static_cast<T>(vec.y));
}

template<typename T>
float v2Len(sf::Vector2<T>& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
void v2AddMag(sf::Vector2<T>& v, float mag)
{
	const auto d = v2Mag(v);
	v.x = (v.x * mag) / d;
	v.y = (v.y * mag) / d;
}

template<typename T, typename U>
auto v2Sub(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	return sf::Vector2(a.x - b.x, a.y - b.y);
}

template<typename T, typename U>
auto v2Sub(sf::Vector2<T>& a, U k)
{
	return sf::Vector2(a.x - k, a.y - k);
}

template<typename T, typename U>
auto v2Add(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	return sf::Vector2<Z>(a.x + b.x, a.y + b.y);
}

template<typename T, typename U>
auto v2Add(sf::Vector2<T>& a, U k)
{
	return sf::Vector2(a.x + k, a.y + k);
}

template<typename T, typename U>
auto v2Mult(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	return sf::Vector2(a.x * b.x, a.y * b.y);
}

template<typename T, typename U, typename Z>
auto v2Mult(sf::Vector2<T>& a, U k)
{
	return sf::Vector2(a.x * k, a.y * k);
}

template<typename T, typename U>
sf::Vector2f v2Div(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	return sf::Vector2f((float) a.x / b.x, (float) a.y / b.y);
}

template<typename T, typename U>
sf::Vector2f v2Div(sf::Vector2<T>& a, U k)
{
	return sf::Vector2f(a.x / k, a.y / k);
}

template<typename T>
sf::Vector2f v2Norm(sf::Vector2<T> v)
{
	return v2Div(v, v2Len(v));
}

template<typename T, typename U>
float v2Dot(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<typename T, typename U>
float v2Dist(sf::Vector2<T>& a, sf::Vector2<U>& b)
{
	const float dx = 1.0 * a.x - b.x;
	const float dy = 1.0 * a.y - b.y;
	return std::sqrt(dx * dx + dy * dy);
}

END_NAMESPACE
