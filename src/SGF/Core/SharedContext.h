#pragma once
#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "Window.h"

SGF_NAMESPACE(::Core)

struct GroupAssets
{
	AssetManager<sf::Texture> textures;
	AssetManager<sf::Font> fonts;
};

struct SharedContext
{
	InputManager Input;
	GroupAssets Assets;
	EventManager Events;
	unique_ptr<Window> Window;
};

using pSharedContext = shared_ptr<SharedContext>;

inline pSharedContext CreateSharedContext(const std::string& name, sf::VideoMode mode)
{
	auto ctx = std::make_shared<SharedContext>();

	ctx->Window = std::make_unique<Window>(ctx->Events);
	ctx->Window->Create(name, mode);
	
	ctx->Input = { *ctx->Window->getSFWindow() };
	return ctx;
}

END_NAMESPACE

 
