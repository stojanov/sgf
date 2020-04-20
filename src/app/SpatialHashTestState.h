#pragma once
#include "Core/State.h"

class SpatialHashTestState: public sgf::Core::State
{
public:
	SpatialHashTestState(sgf::Core::pSharedContext ctx);

	void Init() override;
	
	void Resume() override;
	void Pause() override;
private:
};