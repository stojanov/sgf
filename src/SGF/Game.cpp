#include "Game.h"

#include "Utilities/IO.h"

SGF_NAMESPACE()

void Game::PopState()
{
	m_States.Pop();
}

Game::Game()
{
	m_Ctx = Core::CreateSharedContext("Test", sf::VideoMode(800, 600));
}

void Game::Run()
{
	constexpr float fixedDt = 0.1f;
	float newTime, frameTime, interpolation = 0;

	float currentTime = m_Clock.getElapsedTime().asSeconds();
	float acc = 0;

	while (m_Ctx->Window->getSFWindow()->isOpen())
	{
		//m_Ctx->Window->getSFWindow()->clear();
		m_States.ProcessStates();

		newTime = m_Clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime;

		if (frameTime > fixedDt) // limit dt in case of pause / out of focus
		{
			frameTime = fixedDt;
		}

		currentTime = newTime;
		acc += frameTime;

		// Simulate delay between frames in case of lag spikes
		while (acc >= m_dt)
		{
			m_Ctx->Window->HandleEvents();
			m_States.getActiveState()->Update(m_dt);

			acc -= m_dt;
		}

		interpolation = acc / m_dt;

		m_States.getActiveState()->Draw(interpolation);

		m_Ctx->Window->Display();
	}
}

END_NAMESPACE
