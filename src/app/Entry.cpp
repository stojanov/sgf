#include "Game.h"
#include "MainScreen.h"

/*
#ifdef NDEBUG
#ifdef WIN32
#include <Windows.h>
bool SHOW_CONSOLE = ShowWindow(GetConsoleWindow(), 0);
#endif
#endif
*/

int main() 
{
	sgf::Game g;

	g.PushState<MainScreen>();
	g.Run();
	
	int k;
	std::cin >> k;
}
