#include "Worker.h"

#include <thread>

SGF_NAMESPACE(::System)
	
Worker::~Worker() = default;

bool Worker::StartWork()
{
	if (m_WorkerStarted)
	{
		return false;
	}

	m_WorkerDone = false;
	m_WorkerStarted = true;

	m_Worker = std::thread([&]()
	{
		Job();
		Done();
		m_WorkerDone = true;
		m_WorkerStarted = false;
	});

	return true;
}

void Worker::Wait()
{
	if (!m_WorkerStarted) { return; }
	m_Worker.join();
}
/*

void Worker::Stop()
{
	m_Worker.~thread();
}

 */

END_NAMESPACE