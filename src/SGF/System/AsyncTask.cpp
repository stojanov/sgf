#include "AsyncTask.h"

#include <thread>

SGF_NAMESPACE(::System)

AsyncTask::AsyncTask(voidCallback fn)
{
	m_JobFn = fn;
}
	
AsyncTask::AsyncTask(AsyncTask& t)
{
	m_WorkerDone = false;
	m_WorkerStarted = false;
	m_JobFn = t.m_JobFn;
}

AsyncTask& AsyncTask::operator=(const AsyncTask& t)
{
	m_WorkerDone = false;
	m_WorkerStarted = false;
	m_JobFn = t.m_JobFn;
	
	return *this;
}

bool AsyncTask::StartWork()
{
	if (!m_JobFn || m_WorkerStarted) { return false; }

	m_WorkerDone = false;
	m_WorkerStarted = true;

	m_Worker.swap(std::thread([&]()
	{
		m_JobFn();
		m_WorkerDone = true;
		m_WorkerStarted = false;
	}));

	return true;
}

void AsyncTask::Wait()
{
	if (!m_WorkerStarted) { return; }
	m_Worker.join();
}

END_NAMESPACE