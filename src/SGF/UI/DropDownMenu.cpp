#include "DropDownMenu.h"

SGF_NAMESPACE(::UI)

DropDownMenu::DropDownMenu(Core::pSharedContext ctx)
	:
	UIComponent(ctx),
	m_ShowButton(ctx)
{
	m_ShowButton.SetPosition(m_Pos);
	m_ShowButton.UseContSize(true);
	m_ShowButton.setClickFunction([&]()
		{
			m_IsShown = !m_IsShown;

			if (m_IsShown)
			{
				for (auto& btn : m_Buttons)
					btn->Activate();
			}
			else
			{
				for (auto& btn : m_Buttons)
					btn->Deactivate();
			}
		});
}

DropDownMenu::~DropDownMenu() = default;

void DropDownMenu::SetFont(sf::Font& font)
{
	m_Font = &font;

	m_ShowButton.SetFont(*m_Font);
}

void DropDownMenu::SetName(const string& name)
{
	m_ShowButton.SetText(name);
}

void DropDownMenu::CreateOption(const string& title, System::voidCallback fn)
{
	auto btn = std::make_unique<Button>(m_Ctx);
	
	ASSERT(m_Font);
	
	btn->UseContSize(true);
	btn->SetSize(m_BtnSize);
	btn->SetFont(*m_Font);
	btn->SetText(title);
	btn->setClickFunction(fn);
	

	if (m_CharSize != 0) btn->SetCharSize(m_CharSize);

	m_Buttons.push_back(std::move(btn));
	__updatePosition();
}

void DropDownMenu::SetButtonSize(int x, int y)
{
	m_BtnSize = { (float) x , (float) y };
	__updateSize();
}

void DropDownMenu::SetCharSize(unsigned size)
{
	m_CharSize = size;
	__updateCharSize();
}

void DropDownMenu::SetPosition(float x, float y)
{
	m_Pos = { x, y };
	__updatePosition();
}

void DropDownMenu::Update(float dt)
{
	
}

void DropDownMenu::Draw(float dt)
{
	m_ShowButton.Draw(dt);
	if (m_IsShown)
	{
		for (auto& btn : m_Buttons)
			btn->Draw(dt);
	}
}


END_NAMESPACE