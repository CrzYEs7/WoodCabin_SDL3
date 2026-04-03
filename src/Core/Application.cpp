#include "Application.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include <iostream>

namespace Core {
	static Application* s_Application = nullptr;

	Application::Application(ApplicationSpecifications AppSpecs)
		:m_Specs(AppSpecs)
	{
		s_Application = this;

		if (m_Specs.WindowSpecs.Name.empty()) {
			m_Specs.WindowSpecs.Name = m_Specs.Name;
		}
		SDL_SetAppMetadata(m_Specs.Name.c_str(), "0.69", m_Specs.Name.c_str());

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		}

		if (!SDL_CreateWindowAndRenderer(
					m_Specs.WindowSpecs.Name.c_str(),
					m_Specs.WindowSpecs.Width,
					m_Specs.WindowSpecs.Height,
					SDL_WINDOW_RESIZABLE,
					&m_Window,
					&m_Renderer)) 
		{
			SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		}

		SDL_SetRenderLogicalPresentation(
				m_Renderer,
				m_Specs.WindowSpecs.Width,
				m_Specs.WindowSpecs.Height,
				SDL_LOGICAL_PRESENTATION_LETTERBOX
				);
	}

	void Application::Run(App* app)
	{
		m_Running = true;


		Uint64 startTime = SDL_GetPerformanceCounter();
		Uint64 endTime = SDL_GetPerformanceCounter() - 20;
		int fpsTarget = m_Specs.WindowSpecs.FPS;
		float fpsCurrent = 0;

		if(app->kind != AppKind::Nil)
		{
			app->Run();
		}
		else
		{
			SDL_Log("From Application AppKind is: %i", app->kind);
		}
		while(m_Running)
		{
			// get delta and limit fps
			startTime = SDL_GetPerformanceCounter();
			const float delta = (startTime - endTime) / (float)SDL_GetPerformanceFrequency() * 1000.0f; 
			endTime = startTime;

			fpsCurrent = 1000.0f/delta;
			// std::cout << "fps:" << fpsCurrent << std::endl;
			SDL_DelayNS(SDL_floor((Uint64)(1000000000/fpsTarget) - delta));	
			
			SDL_Event event;
			while (SDL_PollEvent(&event)) 
			{
				switch (event.type)
				{
					case SDL_EVENT_QUIT:
						m_Running = false;	
						SDL_Quit();
						break;
				}
				app->ProcessEvents(event);
			}

			app->Update(delta);
			app->Render();
		}
	}
}
