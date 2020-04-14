#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Namespace.h"

SGF_NAMESPACE()

class Collidable
{
public:
	virtual sf::FloatRect getBoundingBox() = 0;
	virtual ~Collidable() = default;

	void setID(size_t i)
	{
		ID = i;
	}

	size_t getID()
	{
		return ID;
	}
private:
	// The container that creates the collidable object should set the ID property
	size_t ID{ 0 };
};

END_NAMESPACE