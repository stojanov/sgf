#include "StateMachine.h"

#include "System/Log.h"
#include "System/Debug.h"

SGF_NAMESPACE(::Core)

StateMachine::StateMachine() {};

StateMachine::~StateMachine() = default;

void StateMachine::Pop()
{
	m_CurrentJob = REMOVE;
}

void StateMachine::Push(pState& statePtr, bool replacing)
{
	m_NewState = std::move(statePtr);
	DSTATELOG << "(QUEUED): " << m_NewState->GetID() << (replacing ? " - REPLACING" : "");

	if (replacing)
	{
		m_CurrentJob = REPLACE;
	}
	else
	{
		m_CurrentJob = ADD;
	}
}

void StateMachine::ProcessStates()
{
	switch (m_CurrentJob)
	{
	case NONE: break;
	case ADD:
		DSTATELOG << "(ADD) : " << m_NewState->GetID();

		if (!m_Stack.empty())
		{
			m_Stack.top()->Pause();
		}
		else
		{
			DSTATELOG << "EMPTY STACK";
		}

		m_Stack.push(std::move(m_NewState));
		m_Stack.top()->Init();

		m_CurrentJob = NONE;
		break;
	case REPLACE:
		DSTATELOG << "(REPLACE) : " << m_NewState->GetID();
		if (!m_Stack.empty())
		{
			m_Stack.pop();
			m_CurrentJob = ADD;
		}
		else
		{
			m_CurrentJob = NONE;
			DSTATELOG << "EMPTY STACK";
		}
		break;
	case REMOVE:
		DSTATELOG << "(REMOVE) : " << m_NewState->GetID();
		if (!m_Stack.empty())
		{
			m_Stack.pop();

			if (!m_Stack.empty())
			{
				m_Stack.top()->Resume();
			}
		}
		else
		{
			DSTATELOG << "EMPTY STACK";
		}

		m_CurrentJob = NONE;
		break;
	}
}

pState& StateMachine::getActiveState() 
{
	return m_Stack.top();
}

END_NAMESPACE
