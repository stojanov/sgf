#include "MainScreen.h"

#include "Core/CoreTypes.h"
#include "UI/Button.h"
#include "Examples/NoiseTest.h"
#include "UI/Handler.h"
#include "UI/StackMenu.h"
#include "UI/DropDownMenu.h"

using namespace sgf;

MainScreen::MainScreen(Core::pSharedContext ctx)
	: State(ctx)
{
	m_ID = "Main Screen";

	auto font = Core::LoadFont("font.ttf");
	
	auto NoiseLayer = m_Renderer.Attach<NoiseTest>("noiseTest");
	auto UI = m_Renderer.Attach<UI::Handler>("UI");
	
	UI->setDefaultFont(font);
	
	auto menu = UI->Create<UI::DropDownMenu>("menus");

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

void MainScreen::Init()
{
}

void MainScreen::Pause()
{
}

void MainScreen::Resume()
{
}
