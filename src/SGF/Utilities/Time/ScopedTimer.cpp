#include "ScopedTimer.h"
#include "System/Log.h"

SGF_NAMESPACE(::Util)

ScopedTimer::ScopedTimer(const std::string& name, Time type)
	:
	BaseTimer(name, type)
{}

ScopedTimer::~ScopedTimer()
{
	ILOG << m_Name << " took " << _getDuration(m_Type) << _getType(m_Type); 
}

END_NAMESPACE