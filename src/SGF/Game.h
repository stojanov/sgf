#pragma once
#include <SFML/System/Clock.hpp>
#include "Core/CoreTypes.h"
#include "Core/Window.h"
#include "Core/StateMachine.h"

SGF_NAMESPACE()
	
class Game
{
public:
	Game();
	~Game() = default;

	void Run();

	template<typename T>
	void PushState()
	{
		std::unique_ptr<Core::State> ptr(new T(m_Ctx));
		m_States.Push(ptr, false);
	}
	
	template<typename T>
	void ReplaceState()
	{
		std::unique_ptr<Core::State> ptr(new T(m_Ctx));
		m_States.Push(ptr, true);
	}

	void PopState();
private:
	const float m_dt = 1.f / 60.0f;
	sf::Clock m_Clock;
	Core::StateMachine m_States;
	Core::pSharedContext m_Ctx;
};

END_NAMESPACE
