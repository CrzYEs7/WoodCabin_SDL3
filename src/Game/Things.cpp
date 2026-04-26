#include "Things.h"

namespace Game
{
	int Things::Add(Kind kind)
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
