#pragma once
#include <unordered_map>

#include "System/Debug.h"
#include "Core/CoreTypes.h"
#include "Components/RenderComponent.h"
#include "Components/UIComponent.h"

using std::string;
using std::unordered_map;

SGF_NAMESPACE(::UI)

class Handler: public RenderComponent
{	
public:
	Handler(Core::pSharedContext ctx);
	~Handler();
	
	template<typename T, typename = typename std::enable_if<std::is_base_of<UIComponent, T>::value>::type>
	T* Create(const string& name)
	{
		m_Ctx->Events.BindComponent(this);
		
		UIComponent* obj = new T(m_Ctx);
		/*
		if (m_UsingTransform)
			obj->AddTransform(m_View);
		*/
		T* rtnPtr = dynamic_cast<T*>(obj);
		
		m_Objects.insert({ name, obj });

		if (m_DefaultFont && obj->UsesFont())
		{
			rtnPtr->SetFont(*m_DefaultFont);
		}

		return rtnPtr;
	}

	template<typename T>
	T* GetAs(const string& name)
	{
		return dynamic_cast<T*>(Get(name));
	}

	UIComponent* Get(const string& name)
	{
		auto ptr = m_Objects.find(name);

		ASSERT(ptr != m_Objects.end());

		return ptr->second; 
	}

	void onActivation() override;
	void onDeactivation() override;
	
	void setDefaultFont(Core::pFont font);
	void Update(float dt) override;
	void Draw(float dt) override;
private:
	unordered_map<string, UIComponent*> m_Objects;
	Core::pFont m_DefaultFont{ nullptr };
};

END_NAMESPACE
