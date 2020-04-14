#pragma once
#include "Core/SharedContext.h"
#include "Namespace.h"

SGF_NAMESPACE()

class Renderable
{
public:
	Renderable(Core::pSharedContext ctx);
	virtual ~Renderable() = default;
	
	virtual void Draw(float dt) = 0;
	virtual void Update(float dt) = 0;
	
protected:
	Core::pSharedContext m_Ctx;
};
	
END_NAMESPACE
