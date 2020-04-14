#include "State.h"

SGF_NAMESPACE(::Core)

State::State(pSharedContext ctx)
	: Renderable(ctx), m_Renderer(m_Ctx)
{
}

void State::Update(float dt)
{
	m_Renderer.Update(dt);
}

void State::Draw(float dt)
{
	m_Renderer.Draw(dt);
}

END_NAMESPACE