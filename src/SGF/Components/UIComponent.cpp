#include "UIComponent.h"
#include "Core/SharedContext.h"

SGF_NAMESPACE()

UIComponent::UIComponent(Core::pSharedContext ctx)
	:	Renderable(ctx) {}
	
END_NAMESPACE