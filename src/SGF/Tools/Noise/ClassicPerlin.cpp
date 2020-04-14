#include "ClassicPerlin.h"
#include "2DNoise.h"
#include "1DNoise.h"

SGF_NAMESPACE(::Tools)

ClassicPerlin::ClassicPerlin(unsigned int octaves, float persistence)
	: m_octaves(octaves),
	m_persistence(persistence) {}

void ClassicPerlin::offsetX(SGF_DECIMAL x)
{
	m_offsetX += x;
}

void ClassicPerlin::offsetY(SGF_DECIMAL y)
{
	m_offsetY += y;
}

void ClassicPerlin::setXOffset(SGF_DECIMAL x)
{
	m_offsetX = x;
}

void ClassicPerlin::setYOffset(SGF_DECIMAL y)
{
	m_offsetY = y;
}

void ClassicPerlin::setScale(SGF_DECIMAL s)
{
	m_scale = s;
}

void ClassicPerlin::offsetScale(SGF_DECIMAL s)
{
	m_scale *= s;
}

SGF_DECIMAL ClassicPerlin::Perlin1(SGF_DECIMAL x) const
{
	return CosineSmoothNoise1(
		(m_scale * (x + static_cast<double>(m_offsetX))),
		1
	);
}
	
SGF_DECIMAL ClassicPerlin::Perlin2(SGF_DECIMAL x, SGF_DECIMAL y) const
{
	return CosineSmoothNoise2(
		(m_scale * (x + static_cast<double>(m_offsetX))),
		(m_scale * (y + static_cast<double>(m_offsetY))),
		1
	);
}

SGF_DECIMAL ClassicPerlin::Fractal1(SGF_DECIMAL x) const
{
	SGF_DECIMAL total = 0;

	for (unsigned int i = 0; i < m_octaves - 1; i++)
	{
		const SGF_DECIMAL freq = pow(2, i);
		const SGF_DECIMAL amplitude = pow(m_persistence, i);
		total += CosineSmoothNoise1(
			(m_scale * (x + static_cast<double>(m_offsetX)))* freq,
			(i % PRIME_LEN)
		)* amplitude;
	}

	return total;
}
	
SGF_DECIMAL ClassicPerlin::Fractal2(SGF_DECIMAL x, SGF_DECIMAL y) const
{
	SGF_DECIMAL total = 0;

	for (unsigned int i = 0; i < m_octaves - 1; i++)
	{
		const SGF_DECIMAL freq = pow(2, i);
		const SGF_DECIMAL amplitude = pow(m_persistence, i);
		total += CosineSmoothNoise2(
			(m_scale * (x + static_cast<double>(m_offsetX))) * freq,
			(m_scale * (y + static_cast<double>(m_offsetY))) * freq,
			(i % PRIME_LEN)
		) * amplitude;
	}

	return total;
}

END_NAMESPACE
