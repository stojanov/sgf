#pragma once

#include "Utilities/Vec.h"
#include "Components/UIComponent.h"

SGF_NAMESPACE(::UI)
	
// T should have a getGlobalBounds method
template<typename T>
class Clickable: public UIComponent
{	
public:
	void setClickFunction(System::voidCallback f)
	{
		m_ClickContainer = f;
	}

	void setRollOnFunction(System::voidCallback f)
	{
		m_HoverFunction = f;
	}

	void setRollOutFunction(System::voidCallback f)
	{
		m_RolloutFunction = f;
	}

	void Activate()
	{
		m_Activated = true;
	}
	void Deactivate()
	{
		m_Activated = false;
	}

private:
	T* m_ClickableContainer; // sf::RectangeShape or a sprite;
	System::voidCallback m_ClickContainer;
	System::voidCallback m_HoverFunction;
	System::voidCallback m_RolloutFunction;
	bool m_Activated{ true };

	void _HandleEvent(sf::Event& e)
	{
		if (!m_Activated) return;

		if (m_ClickableContainer->getGlobalBounds()
			.contains(Util::v2Cast<float>(m_Ctx->Input.MousePosWindow())))
		{
			if (!m_IsHovering)
			{
				onRollOn();
				if (m_HoverFunction) m_HoverFunction();
			}

			m_IsHovering = true;

			if (m_Ctx->Input.LMousePressedEvent(e))
			{
				onClick();
				if (m_ClickContainer) m_ClickContainer();
			}
		}
		else
		{
			if (m_IsHovering)
			{
				onRollOut();
				if (m_RolloutFunction)
					m_RolloutFunction();
			}
			m_IsHovering = false;
		}

		onEvent(e);
	}
	
	
protected:
	bool m_IsHovering{ false };
	
	Clickable(T* container, Core::pSharedContext ctx)
		:
		UIComponent(ctx),
		m_ClickableContainer(container)
	{
		m_Ctx->Events.AttachCustomEvent(
			std::bind(&Clickable::_HandleEvent, this, std::placeholders::_1)
		);
	}

	virtual ~Clickable() = default;
	
	virtual void onClick() { }
	virtual void onRollOn() { }
	virtual void onRollOut() { }
	virtual void onEvent(sf::Event& e) { }
};

END_NAMESPACE
