#include "Timer.h"
#include "System/Log.h"

SGF_NAMESPACE(::Util)

Timer::Timer(const std::string& name, Time type)
	:
	BaseTimer(name, type)
{}

Timer::~Timer()
{	}

void Timer::StartCount()
{
	m_Clk.restart();
}

void Timer::EndCount()
{
	m_Count = m_Clk.getElapsedTime();
}

float Timer::GetCount()
{
	return _getDuration(m_Count, m_Type);
}

float Timer::GetCount(Time type)
{
	return _getDuration(m_Count, type);
}

void Timer::PrintCount()
{
	ILOG << m_Name << " took " << _getDuration(m_Count, m_Type) << _getType(m_Type);
}

END_NAMESPACE