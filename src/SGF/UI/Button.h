#pragma once
#include <SFML/Graphics.hpp>

#include "Clickable.h"

SGF_NAMESPACE(::UI)

class Button : public Clickable<sf::RectangleShape>
{
public:
	Button(Core::pSharedContext ctx);

	const sf::Vector2f& getPosition() const
	{
		return m_Rect.getPosition();
	}

	const sf::Vector2f& getSize() const
	{
		return m_Rect.getSize();
	}

	bool UsesFont() 
	{
		return true;
	}
	
	void SetCharSize(unsigned size);
	void SetFont(sf::Font& font);
	
	void SetText(const std::string& text);
	void SetText(std::string& text);

	void UseContSize(bool b);
	void SetSize(sf::Vector2f size);
	void SetSize(float w, float h); 
	
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f& v);
	
	void Update(float dt) override;
	void Draw(float dt) override;

	void onRollOn() override;
	void onRollOut() override;

private:
	// Defaults
	static constexpr int s_OffsetY{ -5 }; // Some fonts act differently on the rect in sf::Text, adjust for new fonts
	static constexpr int s_CharSize{ 40 };
	static constexpr int s_Padding{ 5 };
	static constexpr int s_BorderSize{ 0 };
	static constexpr int s_Offset{ 2 * s_Padding + 2 * s_BorderSize };
	static const sf::Color* s_fgClr;
	static const sf::Color* s_bgClr;
	static const sf::Color* s_aBgClr;
	static const sf::Color* s_aFgClr;
	static const sf::Color* s_borderClr;
	bool m_UseConstSize{ false };
	sf::Vector2f m_Size;
	sf::RectangleShape m_Rect;
	std::string m_TxtStr;
	sf::Text m_Txt;

	void UpdateTextPosition();
	void UpdateRectSize();

	void UpdateText();
};

END_NAMESPACE
