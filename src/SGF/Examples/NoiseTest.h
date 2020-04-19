#pragma once

#include "Components/RenderComponent.h"
#include "Utilities/PixelBuffer.h"
#include "Tools/Noise/ClassicPerlin.h"
#include "System/Worker.h"
#include "System/WaitGroup.h"
#include "Tools/Noise/ImprovedPerlin.h"

// Quick way to test the noise classes
class NoiseTest : public sgf::RenderComponent, public sgf::System::Worker
{
public:
	enum TYPE
	{
		PERLIN,
		FRACTAL,
		IMPROVED,
		IMPROVED3D,
		MYNOISE
	};

	NoiseTest(sgf::Core::pSharedContext ctx);

	void Create(TYPE t);

	void Update(float dt) override;
	void Draw(float dt) override;

	void Job() override;
	void Done() override;
	 
	void onActivation() override {};
	void onDeactivation() override {};
private:
	unsigned m_TexWidth{ m_Ctx->Window->GetSize().x };
	unsigned m_TexHeight{ m_Ctx->Window->GetSize().y };

	void _createNoise(std::function<float(float, float)> noiseFunc)
	{
		float min = -1;
		float max = 1;
		sf::Uint8 clr[] = { 0, 0, 0, 255 };

		for (int x = 0; x < m_TexWidth; x++)
		{
			for (int y = 0; y < m_TexHeight; y++)
			{
				float n = noiseFunc(x, y);

				if (n > max) max = n;
				if (n < min) min = n;

				const auto k = LinearTranslate(min, max, sf::Uint8(0), sf::Uint8(255), n);

				clr[0] = k;
				clr[1] = k;
				clr[2] = k;

				m_Points.SetPixel(x, y, clr);
			}
		}
	}
	
	sgf::Util::PixelBuffer<sf::Uint8> m_Points{ 4, m_TexWidth, m_TexHeight};
	sgf::Tools::ClassicPerlin m_Noise { 9, 0.7 };
	sgf::Tools::ImprovedPerlin m_ImprovedPerlin { 9, 0.7 };
	std::mutex m_Lock;
	std::condition_variable m_CA;
	int m_RenderType { -1 };
	bool m_Running{ true };
};
