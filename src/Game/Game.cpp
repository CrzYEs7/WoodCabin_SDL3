#include "SDL3/SDL_events.h"
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
	Game::Things m_Things = Game::Things();

	int PlayerIdx = m_Things.Add(Game::Kind::Player);
	m_Player = m_Things.Get(PlayerIdx);
	if(m_Player) 
	{
	    m_Player.name = "CrzYEst";
	    m_Player.position = Vec2{50.0f, 50.0f};
	    m_Player.speed = 10;
	} 
	else
	{
	    std::cout << "Player does not exists\n";
	}
	std::cout << "Game Runs\n";
    }

    void GameApp::Update(float delta)
    {
	for (int i = 0; i < MAX_THINGS; i++)
	{
	    if (! m_Things.isUsed(i))
		continue;
	    // std::cout << "Thing Name: " << m_Things.Get(i).name << std::endl;
	}
    }

    void GameApp::ProcessEvents(SDL_Event event)
    {
	switch (event.type)
	{
	    case SDL_EVENT_MOUSE_MOTION:
		SDL_Log("We got a motion event.");
		SDL_Log("Current mouse position is: (%f, %f)", event.motion.x, event.motion.y);
		break;
	}
    }

    void GameApp::Render()
    {
	SDL_SetRenderDrawColorFloat(RendererHandle, 1, 1, 1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(RendererHandle);

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
