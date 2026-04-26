#include "Layer.h"

namespace Core
{
	int Layers::Add(LayerKind kind)
	{

		int slot = 1;

		if(m_NextEmptySlot < MAX_LAYERS)
		{
			slot = m_NextEmptySlot++;
		}

		if (slot)
		{
			m_Layers[slot] = {};
			m_Layers[slot].kind = kind;
			m_Used[slot] = true;
		}

		return slot;
	}
}
