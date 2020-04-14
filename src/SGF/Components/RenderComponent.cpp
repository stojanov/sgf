#include "RenderComponent.h"

SGF_NAMESPACE()

RenderComponent::RenderComponent(Core::pSharedContext ctx)
	:	Renderable(ctx) {}


void RenderComponent::Activate()
{
	m_IsActive = true;
	onActivation();
}

void RenderComponent::Deactivate()
{
	m_IsActive = false;
	onDeactivation();
}
	
END_NAMESPACE