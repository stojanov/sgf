#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

namespace sgf {
	class Renderable;
	class UIComponent;
}

using std::unique_ptr;
using std::string;
using std::unordered_map;

SGF_NAMESPACE(::Core)

class Window
{
#define IWINDOWLOG Log(INFO, "Window")
#define EWINDOWLOG Log(ERROR, "Window")
using pRenderWindow = unique_ptr<sf::RenderWindow>;
public:
	Window();
	Window(EventManager& events);
	~Window();

	void Create(const std::string& name, sf::VideoMode mode);

	void HandleEvents();
	void Display() const;

	const bool isClosed() const 
	{
		return m_Closed;
	}

	const pRenderWindow& getSFWindow() const
	{
		return m_Window;
	}

	sf::Vector2u GetSize() const
	{
		return m_Window->getSize();
	}

	void Render(UIComponent& win)
	{
		
	}
	
private:
	unique_ptr<sf::RenderWindow> m_Window;
	EventManager* m_Events { nullptr };
	bool m_Closed{ false };

	void ToggleFullscreen();
	void TakeScreenshot() const;
	void onResize();
};

END_NAMESPACE
