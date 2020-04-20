#pragma once

#include "Core/SharedContext.h"
#include "Renderable.h"

SGF_NAMESPACE()

class UIComponent: public Renderable
{
public:
	UIComponent(Core::pSharedContext ctx);
	virtual ~UIComponent() = default;

	virtual bool UsesFont() = 0;
};

END_NAMESPACE
