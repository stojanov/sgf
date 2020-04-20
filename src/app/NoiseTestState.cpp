#include "NoiseTestState.h"

#include "Core/CoreTypes.h"
#include "Examples/NoiseTest.h"
#include "UI/Handler.h"
#include "UI/DropDownMenu.h"
#include "UI/FPSCounter.h"
#include "Examples/SpatialHashTest.h"

using namespace sgf;

NoiseTestState::NoiseTestState(Core::pSharedContext ctx)
	:
	State(ctx)
{
	m_ID = "Main Screen";

	auto font = Core::LoadFont("font.ttf");
	
	auto NoiseLayer = m_Renderer.Attach<NoiseTest>("noiseTest");
	
	auto UI = m_Renderer.Attach<UI::Handler>("UI");
	
	UI->setDefaultFont(font);
	
	auto menu = UI->Create<UI::DropDownMenu>("menus");
	auto FPS = UI->Create<UI::FPSCounter>("fps");

	FPS->SetPosition(UI::FPSCounter::Position::BOT_RIGHT);

	menu->SetCharSize(12);
	menu->SetButtonSize(150, 20);

	menu->SetName("Menu");
	
	menu->CreateOption(
		"Classic Perlin",
		std::bind(&NoiseTest::Create, NoiseLayer, NoiseTest::PERLIN)
	);
	menu->CreateOption(
		"Fractal Perlin",
		std::bind(&NoiseTest::Create, NoiseLayer, NoiseTest::FRACTAL)
	);
	menu->CreateOption(
		"Improved Perlin",
		std::bind(&NoiseTest::Create, NoiseLayer, NoiseTest::IMPROVED)
	);
	menu->CreateOption(
		"Improved 3D Calc",
		std::bind(&NoiseTest::Create, NoiseLayer, NoiseTest::IMPROVED3D)
	);
	
}

void NoiseTestState::Init()
{
}

void NoiseTestState::Pause()
{
}

void NoiseTestState::Resume()
{
}
