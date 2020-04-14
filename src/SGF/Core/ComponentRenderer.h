#pragma once
#include <unordered_map>
#include <memory>
#include <deque>

#include "Components/RenderComponent.h"
#include "SharedContext.h"

using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::deque;

SGF_NAMESPACE(::Core)

/*
 * Main render setup for all states
 * Implemented with a deque to preserve the addition order
 * Insertion O(1)
 * Deletion O(n)
 */
class ComponentRenderer
{
using RenderObjectType = RenderComponent; // This is used to test different classes
public:
	ComponentRenderer();
	ComponentRenderer(pSharedContext ctx);
	~ComponentRenderer();

	void ShouldClearCallbacks(bool b);
	
	template<typename T, typename = typename std::enable_if<std::is_base_of<RenderObjectType, T>::value>::type>
	T* Attach(const string& name, bool active = true)
	{
		RenderObjectType* ptr = new T(m_Ctx);
		
		m_Deque.push_back(ptr);
		m_Map[name] = ptr;
		
		return dynamic_cast<T*>(ptr);
	}
	bool Detach(const string& name);
	
	void Activate(const string& name);
	void Deactivate(const string& name);

	template<typename T>
	T* GetAs(const string& name) const
	{
		return dynamic_cast<T*>(Get(name));
	}

	RenderObjectType* Get(const string& name) const;

	void Update(float dt);
	void Draw(float dt);
private:
	bool m_ShouldClearCallbacks{ true };
	unordered_map<string, RenderObjectType*> m_Map;
	deque<RenderObjectType*> m_Deque;
	pSharedContext m_Ctx;
};

END_NAMESPACE