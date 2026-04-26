#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <iostream>

#include "Application.h"
#include "Layer.h"

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
			SDL_Log("Couldn't create window/renderer: %s\n", SDL_GetError());
		}

		SDL_SetRenderLogicalPresentation(
				m_Renderer,
				m_Specs.WindowSpecs.Width,
				m_Specs.WindowSpecs.Height,
				SDL_LOGICAL_PRESENTATION_LETTERBOX
				);
	}

	// void Application::Run(App* app)
	void Application::Run()
	{
		m_Running = true;
		Uint64 startTime = SDL_GetPerformanceCounter();
		Uint64 endTime = SDL_GetPerformanceCounter() - 20;
		int fpsTarget = m_Specs.WindowSpecs.FPS;
		float fpsCurrent = 0;

		// if(app->kind != AppKind::Nil)
		// {
		// 	app->Run();
		// }
		// else
		// {
		// 	SDL_Log("From Application AppKind is: %i", app->kind);
		// }

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

				for (int i = 0; i < MAX_LAYERS; i++)
				{
					if (!m_Layers.isUsed(i)) continue;

					Layer& layer = m_Layers.Get(i);
					LayerProcessEvent(layer, event);
				}
			}

			for (int i = 0; i < MAX_LAYERS; i++)
			{
				if (!m_Layers.isUsed(i)) continue;

				Layer& layer = m_Layers.Get(i);
				LayerUpdate(layer, delta);
				LayerRender(layer);
			}
		}
	}

	// 	void Application::AddLayer(Layer& layer)
	// {
	// 	int idx = m_Layers.Add(layer.kind);
	// 	if (m_Layers.Get(idx).kind == LayerKind::Nil)
	// 		SDL_Log("Added layer with type Nil.");
	// }
	

	void Application::AddLayer(LayerKind kind)
	{
		int i = m_Layers.Add(kind);

		switch (kind)
		{
			case Core::LayerKind::Game:
				Layer& layer = m_Layers.Get(i);
				layer.m_PlayerIndex = layer.m_Things.Add(Game::Kind::Player);
				Game::Thing& player = layer.m_Things.Get(layer.m_PlayerIndex);
				player.position = Game::Vec2{50,50};
				player.speed = 1;

		};
	}

	void Application::LayerUpdate(Layer& layer, float dt)
	{
		switch (layer.kind)
		{
			case Core::LayerKind::Game:
				for (int i = 0; i < Game::MAX_THINGS; i++)
				{
					if (! layer.m_Things.isUsed(i))
						continue;
					// std::cout << "Thing Name: " << m_Things.Get(i).name << std::endl;

					Game::Thing& thing = layer.m_Things.Get(i);
					thing.position.x += thing.speed * dt;
					thing.position.y += thing.speed * dt;
				}
		}

	}

	void Application::LayerProcessEvent(Layer& layer, SDL_Event event)
	{
		switch (layer.kind)
		{
			case Core::LayerKind::Game:
				switch (event.type)
				{
					case SDL_EVENT_MOUSE_BUTTON_DOWN:
						int thingIdx = layer.m_Things.Add(Game::Kind::Monster);
						Game::Thing& thing = layer.m_Things.Get(thingIdx);
						thing.position.x = event.motion.x;
						thing.position.y = event.motion.y;
						thing.speed = SDL_randf();
						break;
				}
		}
	}

	void Application::LayerRender(Layer& layer)
	{
		switch (layer.kind)
		{
			case Core::LayerKind::Game:

				SDL_SetRenderDrawColorFloat(m_Renderer, 1, 1, 1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

				/* clear the window to the draw color. */
				SDL_RenderClear(m_Renderer);

				// draw square

				SDL_SetRenderDrawColorFloat(m_Renderer, 0, 0, 1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
				for(int i = 0; i < Game::MAX_THINGS; i++)
				{
					if (! layer.m_Things.isUsed(i))
						continue;

					Game::Thing& thing = layer.m_Things.Get(i);
					SDL_FRect rect = {thing.position.x, thing.position.y, 10, 10};
					// SDL_Log("Thing name: %s\n", thing.name.c_str());
					SDL_RenderRect(m_Renderer, &rect);
				}

				/* put the newly-cleared rendering on the screen. */
				SDL_RenderPresent(m_Renderer);

		}
	}
}
