#pragma once
#include "Thread.h"

SGF_NAMESPACE(::System)

class Worker: public Thread
{
public:
	virtual ~Worker();

	bool StartWork() override;
	void Wait() override;

	virtual void Job() = 0;
	virtual void Done() {};
};

END_NAMESPACE
