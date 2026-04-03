#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_stdinc.h"
#include <string>
#define SDL_MAIN_NOIMPL
#include <SDL3/SDL_main.h>

#include "Game.h"
#include <iostream>

namespace Game 
{
    GameApp::GameApp(SDL_Window* window, SDL_Renderer* renderer):
	WindowHandle(window), RendererHandle(renderer)
    {
	kind = Core::AppKind::Game;

    }

    void GameApp::Run()
    {
	int PlayerIdx = m_Things.Add(Game::Kind::Player);
	m_Player = &m_Things.Get(PlayerIdx);

	if(m_Player->kind != Game::Kind::Nil) 
	{
	    m_Player->name = "CrzYEst";
	    m_Player->position = Vec2{50.0f, 50.0f};
	    m_Player->speed = 1;
	} 
	else
	{
	    std::cout << "Player does not exists\n";
	}

	std::cout << "Player name: " << m_Things.Get(PlayerIdx).name << std::endl;
    }

    void GameApp::Update(float delta)
    {
	for (int i = 0; i < MAX_THINGS; i++)
	{
	    if (! m_Things.isUsed(i))
		continue;
	    // std::cout << "Thing Name: " << m_Things.Get(i).name << std::endl;

	    Thing& thing = m_Things.Get(i);
	    thing.position.x += thing.speed * delta;
	    thing.position.y += thing.speed * delta;
	}
    }

    void GameApp::ProcessEvents(SDL_Event event)
    {
	switch (event.type)
	{
	    case SDL_EVENT_MOUSE_BUTTON_DOWN:
		int thingIdx = m_Things.Add(Kind::Monster);
		Thing& thing = m_Things.Get(thingIdx);
		thing.name = "monster" + std::to_string(thingIdx);
		thing.position.x = event.motion.x;
		thing.position.y = event.motion.y;
		thing.speed = SDL_randf();
		break;
	}
    }

    void GameApp::Render()
    {
	SDL_SetRenderDrawColorFloat(RendererHandle, 1, 1, 1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(RendererHandle);

	// draw square

	SDL_SetRenderDrawColorFloat(RendererHandle, 0, 0, 1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
	for(int i = 0; i < MAX_THINGS; i++)
	{
	    if (! m_Things.isUsed(i))
		continue;

	    Thing& thing = m_Things.Get(i);
	    SDL_FRect rect = {thing.position.x, thing.position.y, 10, 10};
	    // SDL_Log("Thing name: %s\n", thing.name.c_str());
	    SDL_RenderRect(RendererHandle, &rect);
	}

	/* put the newly-cleared rendering on the screen. */
	SDL_RenderPresent(RendererHandle);

    }

    int Game::Things::Add(Kind kind)
    {
	int slot = 0;

	if(m_NextEmptySlot < MAX_THINGS)
	    slot = m_NextEmptySlot++;

	if (slot)
	{
	    m_Things[slot] = {};
	    m_Things[slot].kind = kind;
	    m_Used[slot] = true;
	}

	return slot;
    }
}
