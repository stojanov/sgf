#pragma once
#include <mutex>
#include "Namespace.h"

SGF_NAMESPACE(::System)

class WaitGroup
{
public:
	WaitGroup(unsigned count = 0);

	void Set(unsigned count);
	void Add(unsigned count);
	void Wait();
	void Done();

private:
	std::mutex m_Mutex;
	std::condition_variable m_CV;
	int m_Count;
};

END_NAMESPACE