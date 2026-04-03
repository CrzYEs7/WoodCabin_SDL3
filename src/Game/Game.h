#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <string>

#include "App.h"

namespace Game {
    const uint16_t MAX_THINGS = 1028;

    typedef struct
    {
	float x, y;
    } Vec2;

    enum Kind
    {
	Nil,
	Player,
	Monster,
	Prop
    };

    struct Thing
    {
	Kind kind;
	std::string name;
	Vec2 position;
	float speed;

	operator bool()
	{
	    return kind != Kind::Nil;
	}
    };

    class Things
    {
    public:	
        int Add(Kind kind);
    
	bool& isUsed(int idx)
	{
	    return m_Used[idx];
	}
	Thing& Get(int idx)
	{
	    return m_Things[idx];
	}

    private:
        Thing m_Things[MAX_THINGS] = {};
        bool m_Used[MAX_THINGS] = {};
    
	int m_NextEmptySlot = 1;
    };

    class GameApp : public Core::App
    {
    public:
        GameApp(SDL_Window* window, SDL_Renderer* renderer);
	void Run();
    private:
	Game::Things m_Things;
	Game::Thing* m_Player;

	SDL_Window* WindowHandle = NULL;
	SDL_Renderer* RendererHandle = NULL;

	void ProcessEvents(SDL_Event event);
	void ProcessInput();
	void Update(float delta);
	void Render();
    };

}
