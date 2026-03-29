#include "Application.h"

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

	void Application::Run(App& app)
	{
		m_Running = true;

		while (m_Running)
		{
			const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
			double end_frame_time = ((double)SDL_GetTicks()) / 1000.0;
			const double delta = end_frame_time - now;
			
			if(app.kind != App::Nil)
			{
				app.Run();
			}
			while(m_Running)
			{
				app.Update(delta);
				app.Render();

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
					app.ProcessEvents(event);
				}


			}
			end_frame_time = ((double)SDL_GetTicks()) / 1000.0;
		}
	}
}
