#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Components/Renderable.h"

namespace sgf::Tools
{

/*
 * TODO: Implement this
 */
class Quadtree
{

struct TreeNode
{
	
};
	
public:
	Quadtree();

	void RegisterObject();
	void Clear();
	
private:
	sf::FloatRect m_Bounds;


	void _insert();
};
	
}
