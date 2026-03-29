#include "App.h"
#include "Game.h"
#include "Application.h"

int main()
{
	Core::WindowSpecifications WinSpecs;
	WinSpecs.Width = 1024;
	WinSpecs.Height = 720;
	
	Core::ApplicationSpecifications AppSpecs;
	AppSpecs.WindowSpecs = WinSpecs;
	AppSpecs.Name = "Wood Cabin";
	Core::Application Application = Core::Application(AppSpecs);

	Game::GameApp Game = Game::GameApp(Application.get_WindowHandle(), Application.get_RendererHandle());

	Application.Run(&Game);
}
