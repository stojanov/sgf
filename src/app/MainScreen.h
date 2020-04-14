#pragma once

#include "Core/State.h"
#include "Core/SharedContext.h"

class MainScreen : public sgf::Core::State
{
public:
	MainScreen(sgf::Core::pSharedContext ctx);
	void Init() override;

	void Pause() override;
	void Resume() override;
};
