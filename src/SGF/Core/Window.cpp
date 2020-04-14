#include "Window.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "System/Log.h"

// TODO: Finish Window Class
/*
 * Window with a view so it can resize and call 
 * resize on every sprite/drawable with every size update on the window
 */

namespace sgf::Core
{
	
Window::Window() {}
Window::~Window() = default;

Window::Window(EventManager& events)
	:	m_Events(&events) { }

void Window::Create(const std::string& name, sf::VideoMode mode)
{
	m_Window = std::make_unique<sf::RenderWindow>(mode, name);
	//m_Window->setActive(false);
}

void Window::TakeScreenshot() const
{
	sf::Texture texture;
	texture.create(m_Window->getSize().x, m_Window->getSize().y);
	texture.update(*m_Window);

	if (texture.copyToImage().saveToFile("screen.jpg"))
	{
		IWINDOWLOG << "SAVED SCREENSHOT";
	}
	else
	{
		EWINDOWLOG << "ERROR SAVING SCREENSHOT";
	}
}

void Window::ToggleFullscreen()
{
	
}

void Window::HandleEvents()
{
	sf::Event e;

	while (m_Window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;

		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
				case sf::Keyboard::F5: ToggleFullscreen(); break;
				case sf::Keyboard::F12: TakeScreenshot(); break;
				default: break;
			}
			break;
			/*
		case sf::Event::Resized:
			break;
			*/
		default: break;
		}

		m_Events->HandleEvent(e);
	}
}
	
void Window::onResize()
{
	
}

void Window::Display() const
{
	m_Window->display();
}

}
