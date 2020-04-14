#include "EventManager.h"

SGF_NAMESPACE(::Core)

EventManager::EventManager()
{
};

EventManager::~EventManager() = default;

void EventManager::BindComponent(RenderComponent* id)
{
	if (m_BoundID == id) return;
	
	if (const auto& StateEntry = m_Components.find(id); StateEntry != m_Components.end())
	{
		m_BoundComponentPtr = &StateEntry->second;
	}
	else
	{
		auto [itr, err] = m_Components.emplace(id, EventsContainer());
		m_BoundComponentPtr = &itr->second;
	}
	m_BoundID = id;
}

void EventManager::DeactivateComponent(RenderComponent* id)
{
	if (const auto& StateEntry = m_Components.find(id); StateEntry != m_Components.end())
	{
		IEVENTLOG << "DEACTIVATING STATE: " << id;
		StateEntry->second.isActive = false;
	}
}

void EventManager::ActivateComponent(RenderComponent* id)
{
	if (const auto& StateEntry = m_Components.find(id); StateEntry != m_Components.end())
	{
		IEVENTLOG << "ACTIVATING STATE: " << id;
		StateEntry->second.isActive = true;
	}
}

bool EventManager::DeleteComponent(RenderComponent* id)
{
	if (const auto& StateEntry = m_Components.find(id); StateEntry != m_Components.end())
	{
		m_Components.erase(StateEntry);
		m_BoundID = nullptr;
		return true;
	}

	return false;
}

void EventManager::Unbind()
{
	IEVENTLOG << "UNBINDING STATE: " << m_BoundID;
	m_BoundID = nullptr;
}

void EventManager::Activate()
{
	if (!m_BoundID) return;
	m_BoundComponentPtr->isActive = true;
}

void EventManager::Deactivate()
{
	if (!m_BoundID) return;
	m_BoundComponentPtr->isActive = false;
}

void EventManager::AttachEvent(EventType evt, EventCallback callback)
{
	DEVENTLOG << "ADDING EVENT: " << evt << ", BOUND_ID: " << m_BoundID;
	
	if (m_BoundID)
		m_BoundComponentPtr->Callbacks[evt].push_back(callback);
	else 
		m_DefaultEvents.Callbacks[evt].push_back(callback);
}

void EventManager::AttachCustomEvent(EventCallback callback)
{
	IEVENTLOG << "ADDING CUSTOM EVENT, BOUND_ID: " << m_BoundID;
	
	if (m_BoundID)
		m_BoundComponentPtr->CustomEvents.push_back(callback);
	else 
		m_DefaultEvents.CustomEvents.push_back(callback);
}

void EventManager::RemoveEventType(EventType evt)
{
	DEVENTLOG << "REMOVING EVENT, BOUND_ID: " << m_BoundID;
	
	if (m_BoundID)
		m_BoundComponentPtr->Callbacks[evt].clear();
	else
		m_DefaultEvents.Callbacks[evt].clear();
}

void EventManager::DefaultAttachEvent(EventType evt, EventCallback callback)
{
	m_DefaultEvents.CustomEvents.push_back(callback);
}

void EventManager::DefaultCustomEvent(EventCallback callback)
{
	m_DefaultEvents.CustomEvents.push_back(callback);
}

void EventManager::DefaultRemoveEventType(EventType evt)
{
	m_DefaultEvents.Callbacks[evt].clear();
}

void EventManager::AttachStaticEvent(EventType evt, EventCallback callback)
{
	m_StaticCallbacks[evt].push_back(callback);
}

void EventManager::AttachEventOnComponent(const RenderComponent* id, EventType evt, EventCallback callback)
{
	if (const auto StateEntry = m_Components.find(id); StateEntry != m_Components.end())
		StateEntry->second.Callbacks[evt].push_back(callback);
}

void EventManager::AttachCustomEventOnComponent(const RenderComponent* id, EventCallback callback)
{
	if (const auto StateEntry = m_Components.find(id); StateEntry != m_Components.end())
		StateEntry->second.CustomEvents.push_back(callback);
}

void EventManager::HandleEvent(sf::Event& evt)
{
	_HandleEvents(m_DefaultEvents, evt);

	for (auto& itr : m_Components)
	{
		if (!itr.second.isActive) continue;
		_HandleEvents(itr.second, evt);
	}
}

void EventManager::PurgeCallbacks()
{
	_PurgeCallbackContainer(m_StaticCallbacks);
	for (auto& itr : m_Components)
	{
		_PurgeCallbackContainer(itr.second.Callbacks);
		itr.second.CustomEvents.clear();
	}
}

END_NAMESPACE
