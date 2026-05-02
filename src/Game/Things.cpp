#include "Things.h"
#include <stdio.h>

namespace Game
{
	Things::Things()
	{
		for(int i = 0; i < MAX_THINGS ; i++)
		{
			printf("Initialize index: %i, with: %i\n", i, i+1);
			m_FreeList[i].Next = i+1; 
		}
		m_FreeList[MAX_THINGS-1].Next = 0;
	}

	ThingRef Things::Add(Kind kind)
	{
		const int slot = m_FreeList[0].Next;
		m_FreeList[0].Next = m_FreeList[slot].Next;

		if (slot)
		{
			m_Things[slot] = {};
			m_Things[slot].kind = kind;
			m_Used[slot] = true;
			m_Generation[slot] += 1;
		
			printf("Add at index: %i, gen: %i\n", slot, m_Generation[slot]);
			return {slot, m_Generation[slot]};
		}

		printf("Add at index: %i, gen: %i ThingRef::Nil\n", slot, m_Generation[slot]);
		return ThingRef::Nil();
	}

	void Things::Remove(ThingRef ref)
	{
		if (int Slot = Deref(ref))
		{
			m_Used[Slot] = false;
			m_FreeList[Slot].Next = m_FreeList[0].Next;
			m_FreeList[0].Next = Slot;
		}
	}

	int Things::Deref(ThingRef ref)
	{
		if (ref.Index > 0 && m_Generation[ref.Index] == ref.Generation &&
				m_Used[ref.Index] && ref.Index < MAX_THINGS)
		{
			return ref.Index;
		}
		else
		{
			return 0;
		}
	}
}
