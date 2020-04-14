#pragma once

#include "Utilities/Math.h"
#include "Namespace.h"

SGF_NAMESPACE(::Tools)

class ClassicPerlin
{
public:
	ClassicPerlin(unsigned int octaves = 5, float persistence = 0.5);

	SGF_DECIMAL Perlin2(SGF_DECIMAL x, SGF_DECIMAL y) const;
	SGF_DECIMAL Fractal2(SGF_DECIMAL x, SGF_DECIMAL y) const;

	SGF_DECIMAL Perlin1(SGF_DECIMAL x) const;
	SGF_DECIMAL Fractal1(SGF_DECIMAL x) const;

	void offsetX(SGF_DECIMAL x);
	void offsetY(SGF_DECIMAL y);

	void setXOffset(SGF_DECIMAL x);
	void setYOffset(SGF_DECIMAL y);

	void setScale(SGF_DECIMAL s);
	void offsetScale(SGF_DECIMAL s);
private:
	SGF_DECIMAL m_offsetX{0};
	SGF_DECIMAL m_offsetY{0};
	SGF_DECIMAL m_scale{1};
	unsigned m_octaves;
	SGF_DECIMAL m_persistence;
};

END_NAMESPACE
