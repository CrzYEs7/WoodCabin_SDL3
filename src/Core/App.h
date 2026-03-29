#pragma once

#include <SDL3/SDL.h>

namespace Core
{
	enum AppKind
	{
		Nil,
		Game,
		Editor,
	};

	class App
	{
	public:
		AppKind kind = AppKind::Nil;
		virtual void Run() = 0;
		virtual void Render() = 0;
		virtual void Update(float delta) = 0;
		virtual void ProcessEvents(SDL_Event event) = 0;
	};
}
