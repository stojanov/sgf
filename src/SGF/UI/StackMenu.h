#pragma once

#include "Components/UIComponent.h"
#include "Core/SharedContext.h"
#include "Button.h"

SGF_NAMESPACE(::UI)

class StackMenu: public UIComponent
{
public:
	StackMenu(Core::pSharedContext& ctx);
	~StackMenu() {}

	void CreateOption(const std::string& title, System::voidCallback fn);

	void SetCharSize(unsigned size);
	void SetButtonSize(int x, int y);
	void SetPosition(float x, float y);
	void SetOriginFactor(float x, float y); // Origin is based on a factor to multiply the size
	
	bool UsesFont()
	{
		return true;
	}

	void SetFont(sf::Font& font);
	void Update(float dt) override;
	void Draw(float dt) override;
private:
	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::Vector2f m_btnSize { 300.0f, 50 };
	unsigned m_CharSize { 0 };
	sf::Vector2f m_pos;
	sf::Vector2f m_origin;
	sf::Font* m_font { nullptr };

	void updatePosition();
};
	
END_NAMESPACE