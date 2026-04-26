#pragma once 

#include <string>
#include <cstdint>

namespace Game
{
    const uint16_t MAX_THINGS = 1024;

    struct Vec2
    {
    	float x,y;
    };

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
}
