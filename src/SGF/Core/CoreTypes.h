#pragma once

#include "SharedContext.h"
#include "State.h"

SGF_NAMESPACE(::Core)

using pTexture = std::shared_ptr<sf::Texture>;
using pFont = std::shared_ptr<sf::Font>;

inline pFont LoadFont(const std::string& path)
{
	pFont font = std::make_shared<sf::Font>();

	ASSERT(font->loadFromFile(path));

	return font;
}

END_NAMESPACE
