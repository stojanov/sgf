#pragma once

#include <stack>

#include "State.h"

using std::stack;

SGF_NAMESPACE(::Core)
	
class StateMachine
{
#define DSTATELOG Log(DEBUG, "StateMachine")
public:
	StateMachine();
	~StateMachine();

	void Push(pState& statePtr, bool replacing);
	void Pop();
	void ProcessStates();
	const bool isEmpty() const { return m_Stack.empty(); };

	pState& getActiveState();
private:
	enum StateJob
	{
		NONE,
		REPLACE,
		ADD,
		REMOVE
	};

	StateJob m_CurrentJob { NONE };
	stack<pState> m_Stack;
	pState m_NewState;
};

END_NAMESPACE
