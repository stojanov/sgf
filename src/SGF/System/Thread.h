#pragma once
#include <thread>
#include "Namespace.h"

SGF_NAMESPACE(::System)

class Thread
{
public:
	virtual ~Thread() = default;

	virtual bool StartWork() = 0;
	virtual void Wait() = 0;

	const virtual bool IsRunning() const { return !m_WorkerDone && m_WorkerStarted; };
	const virtual bool IsDone() const { return m_WorkerDone && m_WorkerStarted; };
protected:
	bool m_WorkerDone{ false };
	bool m_WorkerStarted{ false };
	std::thread m_Worker;
};

END_NAMESPACE
