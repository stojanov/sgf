#include "WaitGroup.h"
#include <iostream>

SGF_NAMESPACE(::System)

WaitGroup::WaitGroup(unsigned count)
	:
	m_Count(count)
{
}

void WaitGroup::Set(unsigned count)
{
	std::lock_guard<std::mutex> lck(m_Mutex);
	m_Count = count;
}

void WaitGroup::Add(unsigned count)
{
	std::lock_guard<std::mutex> lck(m_Mutex);
	m_Count += count;
}

void WaitGroup::Done()
{
	std::lock_guard<std::mutex> lck(m_Mutex);

	if (m_Count > 0) m_Count--;

	m_CV.notify_all();
}

void WaitGroup::Wait()
{
	std::unique_lock<std::mutex> lck(m_Mutex);
	m_CV.wait(lck, [&]()
		{
			return m_Count == 0;
		});
}

END_NAMESPACE