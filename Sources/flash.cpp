#include "common.hpp"

#define REG32(addr) (*(vu32 *)((void *)((u32)(addr) | 1 << 31)))

namespace CTRPluginFramework
{
	void Flash(u32 color)
	{
		color |= 0x01000000;
		for (u32 i = 0; i < 64; i++)
		{
			REG32(0x10202204) = color;
			svcSleepThread(10000000);
		}
	}
	
	void RandomFlash(MenuEntry *entry)
	{
		if (entry->Hotkeys[0].IsDown())
			Flash(Utils::Random(0, 0xFFFFFF));
		else
			REG32(0x10202204) = 0;
	}
}