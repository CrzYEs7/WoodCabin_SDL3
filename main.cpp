#include "Application.h"
#include "Layer.h"

int main()
{
	Core::WindowSpecifications WinSpecs;
	WinSpecs.Width = 1024;
	WinSpecs.Height = 720;
	

	Core::ApplicationSpecifications AppSpecs;
	AppSpecs.WindowSpecs = WinSpecs;
	AppSpecs.Name = "Wood Cabin";
	Core::Application* Application = new Core::Application(AppSpecs);

	Application->AddLayer(Core::LayerKind::Game);
	Application->Run();

}
