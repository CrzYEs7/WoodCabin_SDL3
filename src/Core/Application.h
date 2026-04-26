#pragma once

#include <SDL3/SDL.h>
#define SDL_MAIN_NOIMPL
#include <string>

#include "Layer.h"

namespace Core {
	
	struct WindowSpecifications {
		std::string Name = "";
		int Width = 800;	
		int Height = 600;
		int FPS = 120;

	};

	struct ApplicationSpecifications {
		std::string Name = "";
		WindowSpecifications WindowSpecs;
	};

	class Application
	{
	public:

		Application(ApplicationSpecifications AppSpecs);
		~Application() = default;		

		SDL_Window* get_WindowHandle()
		{
			return m_Window;
		}
		SDL_Renderer* get_RendererHandle()
		{
			return m_Renderer;
		}

		void LayerUpdate(Layer& layer, float dt);
		void LayerRender(Layer& layer);
		void LayerProcessEvent(Layer& layer, SDL_Event event);

		void AddLayer(LayerKind kind); 
		
		void Run();
		// void Run(App* app);
	private:
		bool m_Running = false;
		ApplicationSpecifications m_Specs = {};
		SDL_Window* m_Window = NULL;
		SDL_Renderer* m_Renderer = NULL;
		Layers m_Layers;

		void Stop();
	};
}
