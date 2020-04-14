#pragma once

#include <string>
#include <memory>
#include "Components/Renderable.h"
#include "ComponentRenderer.h"
#include "SharedContext.h"

using std::string;

SGF_NAMESPACE(::Core)

class State: public Renderable
{
public:
	State(pSharedContext ctx);
	virtual ~State() = default;
	virtual void Init() = 0;

	const string& GetID() const
	{
		return m_ID;
	}

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void Update(float dt) override;
	void Draw(float dt) override;
protected:
	string m_ID;
	ComponentRenderer m_Renderer;
};

using pState = std::unique_ptr<State>;

END_NAMESPACE
