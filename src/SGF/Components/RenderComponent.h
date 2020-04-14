#pragma once
#include "Renderable.h"

SGF_NAMESPACE()

class RenderComponent: public Renderable
{
public:
	RenderComponent(Core::pSharedContext ctx);

	void Deactivate();
	void Activate();

	bool IsActive() const
	{
		return m_IsActive;
	}
protected:
	virtual void onActivation() {};
	virtual void onDeactivation() {};
private:
	bool m_IsActive{ true };
};
	
END_NAMESPACE
