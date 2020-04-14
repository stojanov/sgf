#pragma once
#include <SFML/System/Clock.hpp>
#include "Namespace.h"
#include "Time.h"
#include <string>
#include "BaseTimer.h"

SGF_NAMESPACE(::Util)

class ScopedTimer: public BaseTimer
{
public:
	ScopedTimer(const std::string& name = "", Time type = Miliseconds);
	~ScopedTimer();
};

END_NAMESPACE