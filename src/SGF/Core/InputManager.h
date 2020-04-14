#pragma once

#include "SFML/Graphics.hpp"
#include "Namespace.h"

SGF_NAMESPACE(::Core)
	
class InputManager
{
public:
	InputManager();
	InputManager(sf::RenderWindow& window);
	~InputManager();

	sf::Vector2i MousePosWindow() const
	{
		return sf::Mouse::getPosition(*m_WindowRef);
	}

	static sf::Vector2i MousePosGlobal()
	{
		return sf::Mouse::getPosition();
	}

	static bool LMousePressed()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	static bool RMousePressed()
	{
		return sf::Mouse::isButtonPressed(sf::Mouse::Right);
	}
	
	static bool LMousePressedEvent(sf::Event& e)
	{
		return e.type == sf::Event::MouseButtonPressed
			? e.mouseButton.button == sf::Mouse::Left
			: false;
	}

	static bool RMousePressedEvent(sf::Event& e)
	{
		return e.type == sf::Event::MouseButtonPressed
			? e.mouseButton.button == sf::Mouse::Right
			: false;
	}

	static bool KeyPressed(sf::Keyboard::Key k)
	{
		return sf::Keyboard::isKeyPressed(k);
	}

private:
	sf::RenderWindow* m_WindowRef;
};

END_NAMESPACE
