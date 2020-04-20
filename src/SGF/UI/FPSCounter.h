#pragma once
#include "Components/UIComponent.h"

SGF_NAMESPACE(::UI)

class FPSCounter : public UIComponent
{
public:
	enum class Position
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOT_LEFT,
		BOT_RIGHT,
	};

	FPSCounter(Core::pSharedContext ctx);
	bool UsesFont() override
	{
		return true;
	};

	void SetPosition(Position pos);
	void SetFont(sf::Font& font);

	void Update(float dt) override;
	void Draw(float dt) override;
private:
	static constexpr int m_CharSize{ 15 };
	static constexpr float m_Delay{ 0.1 };
	sf::Text m_Text;
	sf::Clock m_DelayClk;
	float m_Fps{ 0 };
};

END_NAMESPACE