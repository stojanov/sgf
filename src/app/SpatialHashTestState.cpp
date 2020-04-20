#include "SpatialHashTestState.h"
#include "Core/CoreTypes.h"
#include "Examples/SpatialHashTest.h"
#include "UI/Handler.h"
#include "UI/FPSCounter.h"

SpatialHashTestState::SpatialHashTestState(sgf::Core::pSharedContext ctx)
	:
	State(ctx)
{
	m_ID = "Spatial Hash Test";

	auto font = sgf::Core::LoadFont("font.ttf");

	auto testClass = m_Renderer.Attach<SpatialHashTest>("SpatialHash");
	auto UI = m_Renderer.Attach<sgf::UI::Handler>("UI");

	UI->setDefaultFont(font);

	UI->Create<sgf::UI::FPSCounter>("counter");
}

void SpatialHashTestState::Init()
{
	
}

void SpatialHashTestState::Resume()
{
	
}

void SpatialHashTestState::Pause()
{
	
}