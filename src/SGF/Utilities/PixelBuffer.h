#pragma once

#include <memory>
#include "System/Debug.h"

SGF_NAMESPACE(::Util)

template <typename pixelType>
class PixelBuffer: public sf::Drawable
{
public:
	PixelBuffer(unsigned pixelSize = 3, unsigned width = 200, unsigned height = 200)
		:
		m_PixelSize(pixelSize),
		m_Width(width),
		m_Height(height),
		m_Data(new pixelType[pixelSize * width * height])
	{
		m_Tex.create(m_Width, m_Height);
		m_Sprite.setTexture(m_Tex);


		ILOG << "Created PixelBuffer: " << pixelSize << " " << width << " " << height;
	}

	PixelBuffer& operator=(const PixelBuffer& p)
	{
		m_PixelSize = p.m_PixelSize;
		m_Width = p.m_Width;
		m_Height = p.m_Height;

		m_Tex.create(m_Width, m_Height);

		return *this;
	}
	
	void Fill(int clr)
	{
		for (unsigned int i = 0; i < m_Width * m_Height * m_PixelSize; i++)
			m_Data[i] = pixelType(clr);
	}

	const std::unique_ptr<pixelType>& getData() const { return m_Data; }

	void SetPixel(const unsigned x, const unsigned y, pixelType* clrData)
	{
		ASSERT(x >= 0 && x < m_Width);
		ASSERT(y >= 0 && y < m_Height);

		const auto container = m_Data.get();
		pixelType* pixel = &container[(y * m_PixelSize) * m_Width + (x * m_PixelSize)];

		for (unsigned int i = 0; i < m_PixelSize; i++)
			pixel[i] = clrData[i];
	}

	void UpdateTexture()
	{
		m_Tex.update(m_Data.get());
	}
	
	void Draw(sf::RenderTarget& target)
	{
;		target.draw(m_Sprite);
	}

	const unsigned Width() const { return m_Width; }
	const unsigned Height() const { return m_Height; }
	const unsigned Size() const { return m_Width * m_Height * m_PixelSize; }
	const unsigned PixelSize() const { return m_PixelSize; }
	const sf::Sprite& Sprite() const { return m_Sprite; }
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_Sprite);
	}
private:
	unsigned m_PixelSize;
	unsigned m_Width;
	unsigned m_Height;
	std::unique_ptr<pixelType> m_Data{nullptr};
	sf::Texture m_Tex;
	sf::Sprite m_Sprite;
};

END_NAMESPACE
