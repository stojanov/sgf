#include "ComponentRenderer.h"
#include "System/Log.h"

SGF_NAMESPACE(::Core)

ComponentRenderer::ComponentRenderer() = default;

ComponentRenderer::ComponentRenderer(pSharedContext ctx)
	: m_Ctx(ctx)
{
}

void ComponentRenderer::ShouldClearCallbacks(bool b)
{
	m_ShouldClearCallbacks = b;
}

ComponentRenderer::~ComponentRenderer()
{
	if (m_ShouldClearCallbacks) m_Ctx->Events.PurgeCallbacks();

	for (auto i = m_Deque.begin(); i < m_Deque.end(); ++i)
	{
		delete *i;
	}
}

bool ComponentRenderer::Detach(const string& name)
{
	if (auto entry = m_Map.find(name); entry != m_Map.end())
	{
		for (auto i = m_Deque.begin(); i < m_Deque.end(); ++i)
		{
			if (*i == entry->second)
			{
				entry->second->Deactivate();
				m_Deque.erase(i);
				return true;
			}
		}
	}
	return false;
}

void ComponentRenderer::Activate(const string& name) const
{
	if (auto comp = Get(name); comp)
		comp->Activate();
}

void ComponentRenderer::Deactivate(const string& name) const
{
	if (auto comp = Get(name); comp)
		comp->Deactivate();
}

ComponentRenderer::RenderObjectType* ComponentRenderer::Get(const string& name) const
{
	auto ptr = m_Map.find(name);

	if (ptr == m_Map.end())
	{
		ELOG << "Can't find component: " << name;
		return nullptr;
	}

	return ptr->second;
}

void ComponentRenderer::Update(float dt)
{
	for (const auto& ptr : m_Deque)
	{
		if (!ptr->IsActive()) continue;
		ptr->Update(dt);
	}
}

void ComponentRenderer::Draw(float dt)
{
	for (const auto& ptr : m_Deque)
	{
		if (!ptr->IsActive()) continue;
		ptr->Draw(dt);
	}
}

END_NAMESPACE
