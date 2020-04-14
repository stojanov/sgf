#pragma once

#include "Namespace.h"
#include <SFML/System/Clock.hpp>
#include "Time.h"
#include <string>

SGF_NAMESPACE(::Util)

class BaseTimer
{
public:
	BaseTimer(const std::string& name = "", Time type = Miliseconds);
	virtual ~BaseTimer() = default;
protected:
	sf::Clock m_Clk;
	Time m_Type;
	std::string m_Name;

	constexpr char* _getType(Time type)
	{
		switch (type)
		{
		case Seconds: return "s";
		case Miliseconds: return "ms";
		case Microseconds: return "us";
		case Nanoseconds: return "ns";
		}
		return "";
	}
	
	float _getDuration(Time type)
	{
		switch (type)
		{
		case Seconds: return m_Clk.getElapsedTime().asSeconds();
		case Miliseconds: return static_cast<float>(m_Clk.getElapsedTime().asMilliseconds());
		case Microseconds: return static_cast<float>(m_Clk.getElapsedTime().asMicroseconds());
		case Nanoseconds: return m_Clk.getElapsedTime().asMicroseconds() / 1000.f;
		}
	}

	float _getDuration(sf::Time& sfTime, Time type)
	{
		switch (type)
		{
		case Seconds: return sfTime.asSeconds();
		case Miliseconds: return static_cast<float>(sfTime.asMilliseconds());
		case Microseconds: return static_cast<float>(sfTime.asMicroseconds());
		case Nanoseconds: return sfTime.asMicroseconds() / 1000.f;
		}
	}
};

END_NAMESPACE