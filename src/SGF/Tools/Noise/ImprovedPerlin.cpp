#include "ImprovedPerlin.h"
#include "Namespace.h"

SGF_NAMESPACE(::Tools)

ImprovedPerlin::ImprovedPerlin(unsigned octaves, float persistence)
	:
	m_octaves(octaves),
	m_persistence(persistence)
{}

void ImprovedPerlin::offsetX(SGF_DECIMAL x)
{
	m_offsetX += x;
}

void ImprovedPerlin::offsetY(SGF_DECIMAL y)
{
	m_offsetY += y;
}

void ImprovedPerlin::offsetZ(SGF_DECIMAL z)
{
	m_offsetY += z;
}

void ImprovedPerlin::setXOffset(SGF_DECIMAL x)
{
	m_offsetX = x;
}

void ImprovedPerlin::setYOffset(SGF_DECIMAL y)
{
	m_offsetY = y;
}

void ImprovedPerlin::setZOffset(SGF_DECIMAL z)
{
	m_offsetY = z;
}

void ImprovedPerlin::setScale(SGF_DECIMAL s)
{
	m_scale = s;
}

void ImprovedPerlin::offsetScale(SGF_DECIMAL s)
{
	m_scale *= s;
}

SGF_DECIMAL ImprovedPerlin::Perlin2(SGF_DECIMAL x, SGF_DECIMAL y)
{
	int X = static_cast<int>(floor(x)) & 255,
		Y = static_cast<int>(floor(y)) & 255;

	x -= floor(x);
	y -= floor(y);

	SGF_DECIMAL u = fade(x),
				v = fade(y);

	int A = p[X] + Y, AA = p[A], AB = p[A + 1],
		B = p[X + 1] + Y, BA = p[B], BB = p[B + 1];

	return lerp(v, lerp(u, grad(p[AA], x, y, 0),
		grad(p[BA], x - 1, y, 0)),
		lerp(u, grad(p[AB], x, y - 1, 0),
			grad(p[BB], x - 1, y - 1, 0)));
}

SGF_DECIMAL ImprovedPerlin::Perlin3(SGF_DECIMAL x, SGF_DECIMAL y, SGF_DECIMAL z)
{
	int X = static_cast<int>(floor(x)) & 255,
		Y = static_cast<int>(floor(y)) & 255,
		Z = static_cast<int>(floor(z)) & 255;
	
	x -= floor(x);
	y -= floor(y); 
	z -= floor(z);
	
	SGF_DECIMAL u = fade(x),
				v = fade(y),
				w = fade(z);
	
	int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
		B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
		grad(p[BA], x - 1, y, z)), 
		lerp(u, grad(p[AB], x, y - 1, z), 
			grad(p[BB], x - 1, y - 1, z))), 
		lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), 
			grad(p[BA + 1], x - 1, y, z - 1)),
			lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
				grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

SGF_DECIMAL ImprovedPerlin::Fractal2(SGF_DECIMAL x, SGF_DECIMAL y)
{
	SGF_DECIMAL total = 0;
	SGF_DECIMAL freq = 0;
	SGF_DECIMAL amplitude = 0;

	for (unsigned int i = 0; i < m_octaves - 1; i++)
	{
		freq = pow(2, i);
		amplitude = pow(m_persistence, i);

		total += Perlin2(
			(m_scale * (x + static_cast<double>(m_offsetX)))* freq,
			(m_scale * (y + static_cast<double>(m_offsetY)))* freq
		)* amplitude;
	}

	return total;
}

SGF_DECIMAL ImprovedPerlin::Fractal3(SGF_DECIMAL x, SGF_DECIMAL y, SGF_DECIMAL z)
{
	SGF_DECIMAL total = 0;
	SGF_DECIMAL freq = 0;
	SGF_DECIMAL amplitude = 0;
	
	for (unsigned int i = 0; i < m_octaves - 1; i++)
	{
		freq = pow(2, i);
		amplitude = pow(m_persistence, i);

		total += Perlin3(
			(m_scale * (x + static_cast<double>(m_offsetX)))* freq,
			(m_scale * (y + static_cast<double>(m_offsetY)))* freq,
			(m_scale * (z + static_cast<double>(m_offsetZ)))* freq
		) * amplitude;
	}

	return total;
}

END_NAMESPACE
