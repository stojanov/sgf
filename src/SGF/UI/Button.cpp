#include "Button.h"
#include "Theme.h"

SGF_NAMESPACE(::UI)

const sf::Color* Button::s_fgClr = &FOREGROUND_COLOR;
const sf::Color* Button::s_bgClr = &BACKGROUND_COLOR;
const sf::Color* Button::s_aBgClr = &FOREGROUND_COLOR;
const sf::Color* Button::s_aFgClr = &BACKGROUND_COLOR;
const sf::Color* Button::s_borderClr = &BACKGROUND_COLOR;

Button::Button(Core::pSharedContext ctx)
	: Clickable(&m_Rect, ctx)
{
	m_Rect.setFillColor(*s_bgClr);
	m_Rect.setOutlineThickness(s_BorderSize);
	m_Rect.setOutlineColor(*s_borderClr);

	m_Txt.setFillColor(*s_fgClr);
	m_Txt.setCharacterSize(s_CharSize);
}

void Button::SetCharSize(unsigned size)
{
	m_Txt.setCharacterSize(size);

	UpdateText();

	UpdateRectSize();
	UpdateTextPosition();
}

void Button::SetFont(sf::Font& font)
{
	m_Txt.setFont(font);
}

void Button::SetText(std::string& text)
{
	m_TxtStr = std::move(text);
	UpdateText();

	UpdateRectSize();
	UpdateTextPosition();
}

void Button::SetText(const std::string& text)
{
	m_TxtStr = text;
	UpdateText();

	UpdateRectSize();
	UpdateTextPosition();
}

void Button::SetPosition(float x, float y)
{
	m_Rect.setPosition({ x, y });
	UpdateTextPosition();
}

void Button::SetPosition(sf::Vector2f& v)
{
	m_Rect.setPosition(v);
	UpdateTextPosition();
}
	
inline void Button::UpdateText()
{
	std::transform(m_TxtStr.begin(), m_TxtStr.end(), m_TxtStr.begin(), toupper);

	m_Txt.setString(m_TxtStr);
}

inline void Button::UpdateRectSize()
{
	if (m_UseConstSize)
	{
		m_Rect.setSize(m_Size);
	}
	else
	{
		const auto textRect = m_Txt.getGlobalBounds();

		m_Rect.setSize({ textRect.width + s_Offset, textRect.height + s_Offset });
	}
}

inline void Button::UpdateTextPosition()
{
	const auto textRect = m_Txt.getGlobalBounds();

	const auto shapeRect = m_Rect.getGlobalBounds();
	const auto shapePos = m_Rect.getPosition();

	m_Txt.setOrigin(textRect.width / 2, textRect.height / 2);

	m_Txt.setPosition(
		shapePos.x + (shapeRect.width / 2),
		shapePos.y + (shapeRect.height / 2) + s_OffsetY
	);
}

void Button::UseContSize(bool b)
{
	m_UseConstSize = b;
}


void Button::SetSize(sf::Vector2f size)
{
	m_Size = size;
	UpdateRectSize();
}
	
void Button::SetSize(float w, float h)
{
	m_Size = { w, h };
	UpdateRectSize();
}
	
void Button::onRollOut()
{
	m_Rect.setFillColor(*s_bgClr);
	m_Txt.setFillColor(*s_fgClr);
}

void Button::onRollOn()
{
	m_Rect.setFillColor(*s_aBgClr);
	m_Txt.setFillColor(*s_aFgClr);
}

void Button::Update(float dt) {}

void Button::Draw(float dt)
{
	// temporary
	m_Ctx->Window->getSFWindow()->draw(m_Rect);
	m_Ctx->Window->getSFWindow()->draw(m_Txt);
}

END_NAMESPACE

