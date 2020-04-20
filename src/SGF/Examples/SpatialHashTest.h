#pragma once
#include "Components/RenderComponent.h"
#include "Components/Collidable.h"
#include "Tools/SpatialHash.h"

class Particle: public sgf::Renderable, public sgf::Collidable
{
public:
	Particle(sgf::Core::pSharedContext ctx);

	sf::FloatRect getBoundingBox() override 
	{
		return m_Shape.getGlobalBounds();
	}

	void Colliding();
	void NotColliding();
	bool IsIntersecting(Particle& p);
	bool IsIntersecting(sf::FloatRect& rect);
	
	void Update(float dt) override;
	void Draw(float dt) override;
private:
	sf::RectangleShape m_Shape;
	sf::Vector2f m_RandomVel;
	sf::Vector2u m_WindSize;
	sf::Clock m_Clk;
	static constexpr float m_MaxVel{ 50 };
	static constexpr float m_UpdateVelTime{ 0.5 };
	static const inline sf::Vector2f m_ShapeSize{ 5, 5 };
	static const inline sf::Color m_BaseColor{ sf::Color::White };
	static const inline sf::Color m_ActiveColor{ sf::Color::Red };
	void UpdateVel();
};

class SpatialHashTest: public sgf::RenderComponent
{
public:
	SpatialHashTest(sgf::Core::pSharedContext ctx);

	void Update(float dt) override;
	void Draw(float dt) override;
private:
	sgf::Tools::SpatialHash::Map m_Hash{ 6 };
	std::vector<Particle> m_Particles;
	static constexpr int m_ParticleCount{ 500 };
};
