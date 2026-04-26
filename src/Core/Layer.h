#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

#include "Things.h"

namespace Core
{
	const int16_t MAX_LAYERS = 128;

	enum LayerKind
	{
		Nil,
		Game,
		Editor,
		UI
	};

	struct Layer
	{
		LayerKind kind = LayerKind::Nil;

		Game::Things m_Things;
		int m_PlayerIndex;
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

	};

	class Layers
	{
		public:
			int Add(LayerKind kind);
			bool& isUsed(int idx)
			{
				return m_Used[idx];
			};
			Layer& Get(int idx)
			{
				return m_Layers[idx];
			};
		private:
			Layer m_Layers[MAX_LAYERS];
			bool m_Used[MAX_LAYERS];

			int m_NextEmptySlot = 1;
	};
}

