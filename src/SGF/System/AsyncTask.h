#pragma once

#include <functional>

#include "Thread.h"
#include "Core.h"
#include "Namespace.h"

SGF_NAMESPACE(::System)

class AsyncTask: public Thread
{
public:
	AsyncTask(voidCallback fn);
	AsyncTask(AsyncTask& t);
	AsyncTask& operator=(const AsyncTask& t);

	bool StartWork() override;
	void Wait() override;

private:
	voidCallback m_JobFn{ nullptr };
};

END_NAMESPACE
