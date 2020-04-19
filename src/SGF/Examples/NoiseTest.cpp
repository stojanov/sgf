#include "NoiseTest.h"
#include "Utilities/Time/ScopedTimer.h"
#include "Utilities/Time/Timer.h"
#include "Utilities/IO.h"

NoiseTest::NoiseTest(sgf::Core::pSharedContext ctx)
	:
	RenderComponent(ctx) 
{
	m_TexWidth = m_Ctx->Window->GetSize().x;
	m_TexHeight = m_Ctx->Window->GetSize().y;

	m_Noise.setScale(0.01);
	m_ImprovedPerlin.setScale(0.002);
	// Should not call virtual functions inside constructor but it
	// works so its good enough for now
	StartWork();
}

void NoiseTest::Job()
{
	using namespace std::placeholders;
	
	std::unique_lock<std::mutex> lck(m_Lock);
	while (m_Running)
	{
		m_CA.wait(lck, [&]()
			{
				return m_RenderType != -1;
			});

		sgf::Util::ScopedTimer timer("Noise", sgf::Util::Miliseconds);
		
		switch (m_RenderType)
		{
		case PERLIN:
			_createNoise(std::bind(&sgf::Tools::ClassicPerlin::Perlin2, m_Noise, _1, _2));
			break;
		case FRACTAL:
			_createNoise(std::bind(&sgf::Tools::ClassicPerlin::Fractal2, m_Noise, _1, _2));
			break;
		case IMPROVED:
			_createNoise(std::bind(&sgf::Tools::ImprovedPerlin::Fractal2, m_ImprovedPerlin, _1, _2));
			break;
		case IMPROVED3D:
			_createNoise(std::bind(&sgf::Tools::ImprovedPerlin::Fractal3, m_ImprovedPerlin, _1, _2, 1.f));
			break;
		default: break;
		}

		m_RenderType = -1;;
	}
}

void NoiseTest::Create(TYPE t)
{
	if (m_RenderType != -1) return;
	std::lock_guard<std::mutex> lck(m_Lock);
	m_RenderType = t;
	m_CA.notify_one();
}

void NoiseTest::Done() {}

void NoiseTest::Update(float dt)
{
	m_Points.UpdateTexture();
}

void NoiseTest::Draw(float dt)
{
	m_Ctx->Window->getSFWindow()->clear(); // Temporary
	m_Ctx->Window->getSFWindow()->draw(m_Points); // Temporary
}