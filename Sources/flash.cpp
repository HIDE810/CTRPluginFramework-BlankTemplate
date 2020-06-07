#include "common.hpp"

namespace CTRPluginFramework
{
	void RandomFlash(MenuEntry *entry)
	{
		int *p = (int *)0x90202204;
		
		if (entry->Hotkeys[0].IsDown())
		{
			*p = Utils::Random(0, 0xFFFFFF) | 0x01000000;
			
			for (u32 i = 0; i < 64; i++)
				svcSleepThread(10000000);
		}
		else *p = 0;
	}
}