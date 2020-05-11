#pragma once
#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "Window.h"

SGF_NAMESPACE(::Core)

template<typename T>
LoadedAsset<T> sfmlLoadFunction(const std::string& filepath)
{
	auto pShared = std::make_shared<T>();
	return { pShared, pShared->loadFromFile(filepath) } ;
}

struct GroupAssets
{
	AssetManager<sf::Texture> textures{ "textures", sfmlLoadFunction<sf::Texture> };
	AssetManager<sf::Font> fonts{ "fonts", sfmlLoadFunction<sf::Font> };
};

struct SharedContext
{
	InputManager Input;
	GroupAssets Assets;
	EventManager Events;
	unique_ptr<Window> Window;
};

using pSharedContext = shared_ptr<SharedContext>;

inline pSharedContext CreateContext(const std::string& name, sf::VideoMode mode)
{
	auto ctx = std::make_shared<SharedContext>();

	ctx->Window = std::make_unique<Window>(ctx->Events);
	ctx->Window->Create(name, mode);
	
	ctx->Input = { *ctx->Window->getSFWindow() };
	return ctx;
}

END_NAMESPACE

 
