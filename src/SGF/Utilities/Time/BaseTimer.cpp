#include "BaseTimer.h"

SGF_NAMESPACE(::Util)

BaseTimer::BaseTimer(const std::string& name, Time type)
	:
	m_Name(name),
	m_Type(type) {}

END_NAMESPACE