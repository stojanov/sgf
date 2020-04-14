#include "InputManager.h"

SGF_NAMESPACE(::Core)

InputManager::InputManager() {};

InputManager::InputManager(sf::RenderWindow& window)
	: m_WindowRef(&window)
{}

InputManager::~InputManager() {};

END_NAMESPACE
