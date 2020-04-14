#include "StackMenu.h"

SGF_NAMESPACE(::UI)

StackMenu::StackMenu(Core::pSharedContext& ctx)
	:	UIComponent(ctx) {}

void StackMenu::SetFont(sf::Font& font)
{
	m_font = &font;
}

void StackMenu::CreateOption(const std::string& name, System::voidCallback fn)
{
	auto btn = std::make_unique<Button>(m_Ctx);

	btn->UseContSize(true);
	btn->SetSize(m_btnSize);
	btn->SetFont(*m_font);
	btn->SetText(name);
	btn->setClickFunction(fn);

	if (m_CharSize != 0) btn->SetCharSize(m_CharSize);

	m_buttons.push_back(std::move(btn));
	updatePosition();
}

void StackMenu::SetCharSize(unsigned size)
{
	m_CharSize = size;
}
	
void StackMenu::SetButtonSize(int x, int y)
{
	m_btnSize = { (float) x, (float) y };
}

inline void StackMenu::updatePosition()
{
	const float sx = m_pos.x - m_origin.x * m_btnSize.x;
	const float sy = m_pos.y - m_btnSize.y * m_buttons.size() * m_origin.y;

	uint8_t c = 0;
	for (const auto& btn : m_buttons)
		btn->SetPosition(sx, sy + m_btnSize.y * c++);
}

void StackMenu::SetOriginFactor(float x, float y)
{
	m_origin = { x, y };
}

void StackMenu::SetPosition(float x, float y)
{
	m_pos = { x, y };
	updatePosition();
}

void StackMenu::Update(float dt) {}

void StackMenu::Draw(float dt)
{
	for (const auto& btn : m_buttons)
		btn->Draw(dt);
}

END_NAMESPACE