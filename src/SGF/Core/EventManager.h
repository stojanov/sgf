#pragma once

#include <unordered_map>
#include <functional>
#include <array>
#include <SFML/Window/Event.hpp>
#include "System/Log.h"
#include "Namespace.h"

namespace sgf {
	class RenderComponent;
}

using std::unordered_map;
using std::vector;
using std::function;
using std::string;
using std::array;

/*
 * TODO: Redo this class
 * Based on the observer pattern
 * Needs major rework: for every component allocates an array of 23 callbacks
 * Needs to be better and cover more edge cases, very basic and straight forward for now
 * One bug i have experienced is deactivating a component before starting to assign events
 * so it resulted in a miss in the map due to the entry not being created and failed to deactivate, kept adding events
 * very sequential, not made for multithreaded use
 */

/*
 * Not sure if i should pass the callback as a reference
 * and then move the function pointer into the container or should this stay as is
 */
SGF_NAMESPACE(::Core)

using EventType = sf::Event::EventType;
using EventCallback = function<void(sf::Event&)>;

class EventManager
{
#define IEVENTLOG Log(INFO, "EventManager")
#define DEVENTLOG Log(DEBUG, "EventManager")

	using EventCallbacks = vector<EventCallback>;
	using EventCallBackContainer = array<EventCallbacks, EventType::Count>; // Array with fixed size used as a hashmap
	struct EventsContainer
	{
		EventCallBackContainer Callbacks;
		EventCallbacks CustomEvents;
		bool isActive{ true };
	};
	using ComponentMap = unordered_map<const RenderComponent*, EventsContainer>;
	using EventStateMap = unordered_map<string, EventsContainer>;
public:
	EventManager();
	~EventManager();

	void BindComponent(RenderComponent* id);
	void DeactivateComponent(RenderComponent* id);
	void ActivateComponent(RenderComponent* id);
	bool DeleteComponent(RenderComponent* id);

	void Unbind();
	void Deactivate();
	void Activate();
	
	// Bound methods 
	void AttachEvent(EventType evt, EventCallback callback);
	void AttachCustomEvent(EventCallback callback);
	void RemoveEventType(EventType evt);
	// ------------------------------------------------------

	// Will always attach on default container
	void DefaultAttachEvent(EventType evt, EventCallback callback);
	void DefaultCustomEvent(EventCallback callback);
	void DefaultRemoveEventType(EventType evt);
	void AttachStaticEvent(EventType evt, EventCallback callback);
	// ------------------------------------------------------
	
	void AttachEventOnComponent(const RenderComponent* id, EventType evt, EventCallback callback);
	void AttachCustomEventOnComponent(const RenderComponent* id, EventCallback callback);

	void PurgeCallbacks();

	void HandleEvent(sf::Event& evt);
private:
	EventsContainer m_DefaultEvents;
	EventCallBackContainer m_StaticCallbacks;
	EventsContainer* m_BoundComponentPtr { nullptr };
	RenderComponent* m_BoundID{ nullptr };
	string m_BoundState{ " " };
	ComponentMap m_Components;
	
	static void _HandleEvents(EventsContainer& container, sf::Event& evt)
	{
		for (const auto& callback : container.CustomEvents) callback(evt);
		for (const auto& callback : container.Callbacks[evt.type]) callback(evt);
	}

	static void _PurgeCallbackContainer(EventCallBackContainer& arr)
	{
		for (auto& vec : arr) vec.clear();
	}
};

END_NAMESPACE
