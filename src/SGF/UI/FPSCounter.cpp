#include "FPSCounter.h"

SGF_NAMESPACE(::UI)

FPSCounter::FPSCounter(Core::pSharedContext ctx)
    :
	UIComponent(ctx)
{
    m_Text.move(0, 0);
    m_Text.setOutlineColor(sf::Color::Black);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setOutlineThickness(2);
    m_Text.setCharacterSize(m_CharSize);
    m_Text.setString("0");
}

void FPSCounter::SetFont(sf::Font& font)
{
    m_Text.setFont(font);
}

void FPSCounter::SetPosition(Position pos)
{
    const auto winSize = m_Ctx->Window->getSFWindow()->getSize();
	
	switch (pos)
	{
    case Position::TOP_LEFT:
        m_Text.move(0, 0);
		break;
    case Position::TOP_RIGHT:
        m_Text.move((winSize.x - (m_CharSize*3 + 2)), 0);
		break;
    case Position::BOT_LEFT:
        m_Text.move(0, (winSize.y - (m_CharSize + 2)));
		break;
    case Position::BOT_RIGHT:
        m_Text.move((winSize.x - (m_CharSize * 3 + 2)), (winSize.y - (m_CharSize + 2)));
		break;
	}
}


void FPSCounter::Update(float dt)
{
    m_Fps = 1.f / dt;
}

void FPSCounter::Draw(float dt)
{
	if (m_DelayClk.getElapsedTime().asSeconds() > m_Delay)
	{
        m_Text.setString(std::to_string(m_Fps));
        m_DelayClk.restart();
	}
    
    m_Ctx->Window->getSFWindow()->draw(m_Text);
}

END_NAMESPACE