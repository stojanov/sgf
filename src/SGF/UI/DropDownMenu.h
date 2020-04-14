#pragma once
#include "Namespace.h"
#include <vector>
#include "Button.h"

using std::vector;
using std::string;
using std::unique_ptr;

SGF_NAMESPACE(::UI)

class DropDownMenu : public UIComponent
{
public:
	DropDownMenu(Core::pSharedContext ctx);
	~DropDownMenu();

	void CreateOption(const string& title, System::voidCallback fn);

	void SetName(const string& name);
	void SetCharSize(unsigned size);
	void SetButtonSize(int x, int y);
	void SetPosition(float x, float y);

	bool UsesFont() override
	{
		return true;
	}

	void SetFont(sf::Font& font);

	void Update(float dt) override;
	void Draw(float dt) override;
private:
	std::string m_Name;
	vector<unique_ptr<Button>> m_Buttons;
	Button m_ShowButton;
	sf::Vector2f m_BtnSize{ 300.f, 50 };
	sf::Vector2f m_Pos{ 0.f, 0.f };
	sf::Font* m_Font{ nullptr };
	unsigned m_CharSize{ 0 };
	bool m_IsShown{ false };

	void __updatePosition()
	{
		ASSERT(m_Buttons.size() < 255);
		
		uint8_t c = 1;
		for (auto& btn : m_Buttons)
			btn->SetPosition(m_Pos.x, m_Pos.y + m_BtnSize.y * c++);
	}

	void __updateCharSize()
	{
		if (m_CharSize == 0) return;
		m_ShowButton.SetCharSize(m_CharSize);

		for (auto& btn : m_Buttons)
			btn->SetCharSize(m_CharSize);
	}

	void __updateSize()
	{
		m_ShowButton.SetSize(m_BtnSize);

		for (auto& btn : m_Buttons)
			btn->SetSize(m_BtnSize);
	}
};

END_NAMESPACE