#pragma once

#include <SDL3/SDL.h>

namespace Core
{
	class App
	{
	public:
		enum Kind
		{
			Nil,
			Game,
			Editor,
		};
	public:
		Kind kind = Nil;
		virtual void Run() = 0;
		virtual void Render() = 0;
		virtual void Update(float delta) = 0;
		virtual void ProcessEvents(SDL_Event event) = 0;
	};
}
