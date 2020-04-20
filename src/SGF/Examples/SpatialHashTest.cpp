#include "SpatialHashTest.h"
#include "Utilities/Random.h"

Particle::Particle(sgf::Core::pSharedContext ctx)
	:
	Renderable(ctx)
{
	m_WindSize = m_Ctx->Window->getSFWindow()->getSize();

	m_Shape.setPosition(sgf::Util::Random::get().Float(0, m_WindSize.x),
						sgf::Util::Random::get().Float(0, m_WindSize.y));

	UpdateVel();

	m_Shape.setSize(m_ShapeSize);
	m_Shape.setFillColor(m_BaseColor);
}

void Particle::Colliding()
{
	m_Shape.setFillColor(m_ActiveColor);
}

void Particle::NotColliding()
{
	m_Shape.setFillColor(m_BaseColor);
}

void Particle::UpdateVel()
{
	m_RandomVel = { sgf::Util::Random::get().Float(-m_MaxVel, m_MaxVel),
					sgf::Util::Random::get().Float(-m_MaxVel, m_MaxVel) };
}

bool Particle::IsIntersecting(Particle& p)
{
	return m_Shape.getGlobalBounds().intersects(p.getBoundingBox());
}

bool Particle::IsIntersecting(sf::FloatRect& rect)
{
	return m_Shape.getGlobalBounds().intersects(rect);
}

void Particle::Update(float dt)
{
	m_Shape.move(m_RandomVel.x * dt, m_RandomVel.y * dt);

	if (m_Clk.getElapsedTime().asSeconds() > m_UpdateVelTime)
	{
		UpdateVel();
		m_Clk.restart();
	}
	
	auto pos = m_Shape.getPosition();
	// Very crude
	if (pos.x > m_WindSize.x)
	{
		m_Shape.setPosition(10, pos.y);
		return;
	}
	else if (pos.x < 0)
	{
		m_Shape.setPosition(m_WindSize.x - 10, pos.y);
		return;
	}

	if (pos.y > m_WindSize.y)
	{
		m_Shape.setPosition(pos.x, 0);
		return;
	}
	else if (pos.y < 0)
	{
		m_Shape.setPosition(pos.x, m_WindSize.y - 10);
		return;
	}
}

void Particle::Draw(float dt)
{
	m_Ctx->Window->getSFWindow()->draw(m_Shape);
}

SpatialHashTest::SpatialHashTest(sgf::Core::pSharedContext ctx)
	:
	RenderComponent(ctx)
{
	sgf::Util::Random::init();

	m_Particles.reserve(m_ParticleCount);

	for (int i = 0; i < m_ParticleCount; i++)
	{
		m_Particles.emplace_back(ctx);
		m_Particles[i].setID(i);
		m_Hash.RegisterObject(m_Particles[i]);
	}

	/*
	 * It's faster like this but the since it's so fast my random class can't handle
	 * the speed and gives a very bad result
	m_Particles.resize(
		m_ParticleCount,
		{ ctx }
	);*/
}

void SpatialHashTest::Update(float dt)
{
	
	for (auto& p : m_Particles)
	{
		m_Hash.UpdateObject(p);
	}
	
	for (auto& p : m_Particles)
	{
		p.Update(dt);

		auto list = m_Hash.GetRect(p.getBoundingBox());
		for (auto& p2 : list)
		{
			if (p.getID() == p2->getID()) continue;
			
			if (p.IsIntersecting(p2->getBoundingBox()))
			{
				p.Colliding();
			}
			else
			{
				p.NotColliding();
			}
		}
		
	}
}

void SpatialHashTest::Draw(float dt)
{
	for (auto& p : m_Particles)
	{
		p.Draw(dt);
	}
}


