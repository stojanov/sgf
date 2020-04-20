#include "Game.h"

#include "Utilities/IO.h"

SGF_NAMESPACE()

void Game::PopState()
{
	m_States.Pop();
}

Game::Game()
{
	m_Ctx = Core::CreateContext("Test", sf::VideoMode(800, 600));
}

void Game::Run()
{
	float newTime, frameTime, interpolation = 0;

	float currentTime = m_Clock.getElapsedTime().asSeconds();
	float acc = 0;

	while (m_Ctx->Window->getSFWindow()->isOpen())
	{
		m_Ctx->Window->getSFWindow()->clear();
		m_States.ProcessStates();

		newTime = m_Clock.getElapsedTime().asSeconds();
		
		frameTime = newTime - currentTime;

		currentTime = newTime;
		acc += frameTime;

		if (acc > m_LowBoundDt)
		{
			// Simulate delay between frames in case of lag spikes
			while (acc >= m_LowBoundDt)
			{
				m_Ctx->Window->HandleEvents();
				m_States.getActiveState()->Update(m_LowBoundDt);

				acc -= m_LowBoundDt;
			}
			interpolation = acc / m_LowBoundDt;
		}
		else
		{
			m_Ctx->Window->HandleEvents();
			m_States.getActiveState()->Update(frameTime);
			acc -= frameTime;
			interpolation = acc / frameTime;
		}

		m_States.getActiveState()->Draw(interpolation);

		m_Ctx->Window->Display();
	}
}

END_NAMESPACE
