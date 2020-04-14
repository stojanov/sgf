#include "Handler.h"
#include "Core/CoreTypes.h"

SGF_NAMESPACE(::UI)

Handler::Handler(Core::pSharedContext ctx)
	:	RenderComponent(ctx)
{
	m_Ctx->Events.BindComponent(this);
}

Handler::~Handler()
{
	for (const auto& i : m_Objects)
	{
		delete i.second;
	}

	m_Objects.clear();
	m_Ctx->Events.DeleteComponent(this);
}

void Handler::onActivation()
{
	m_Ctx->Events.ActivateComponent(this);
}

void Handler::onDeactivation()
{
	m_Ctx->Events.DeactivateComponent(this);
}
	
void Handler::setDefaultFont(Core::pFont font)
{
	m_DefaultFont = font;
}

void Handler::Update(float dt)
{
	for (const auto& i : m_Objects)
	{
		i.second->Update(dt);
	}
}

void Handler::Draw(float dt)
{
	for (const auto& i : m_Objects)
	{
		i.second->Draw(dt);
	}
}

END_NAMESPACE

