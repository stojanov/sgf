#pragma once

#include "Core/State.h"
#include "Core/SharedContext.h"

class NoiseTestState : public sgf::Core::State
{
public:
	NoiseTestState(sgf::Core::pSharedContext ctx);
	void Init() override;

	void Pause() override;
	void Resume() override;
};
