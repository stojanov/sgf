#pragma once

#include "Namespace.h"
#include <string>
#include "Time.h"
#include "BaseTimer.h"

SGF_NAMESPACE(::Util)

class Timer: public BaseTimer
{
public:
	Timer(const std::string& name = "", Time type = Miliseconds);
	~Timer();
	
	void StartCount();
	void EndCount();
	float GetCount();
	float GetCount(Time type);
	void PrintCount();
	
private:
	sf::Time m_Count;
;};

END_NAMESPACE
