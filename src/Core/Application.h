#include <SDL3/SDL.h>
#include <string>

#include "App.h"

namespace Core {
	
	struct WindowSpecifications {
		std::string Name = "";
		int Width = 800;	
		int Height = 600;
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


		void Run(App& app);
	private:
		bool m_Running = false;
		ApplicationSpecifications m_Specs = {};
		SDL_Window* m_Window = NULL;
		SDL_Renderer* m_Renderer = NULL;

		void Stop();
	};
}


