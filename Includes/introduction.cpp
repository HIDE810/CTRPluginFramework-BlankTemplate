#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	void introduction(MenuEntry *entry)
	{
		OSD::Run([](const Screen &screen)
		{
			if (!screen.IsTop)
				return false;
			screen.DrawRect(0, 0, 400, 240, Color::Black);
			screen.DrawSysfont(Utils::Format("An exception occurred"), 10, 10, Color::Red);
			screen.DrawSysfont(Utils::Format("Processor:          ARM9"), 10, 35);
			screen.DrawSysfont(Utils::Format("Exception type:  undfined introduction"), 10, 47);
			screen.DrawSysfont(Utils::Format("R0      00000000       R1      00000000"), 10, 72);
			screen.DrawSysfont(Utils::Format("R2      00000000       R3      00000000"), 10, 84);
			screen.DrawSysfont(Utils::Format("R4      00000000       R5      00000000"), 10, 96);
			screen.DrawSysfont(Utils::Format("R6      00000000       R7      00000000"), 10, 108);
			screen.DrawSysfont(Utils::Format("R8      00000000       R9      00000000"), 10, 120);
			screen.DrawSysfont(Utils::Format("R10   00000000       R11   00000000"), 10, 132);
			screen.DrawSysfont(Utils::Format("R12   00000000       SP      00000000"), 10, 144);
			screen.DrawSysfont(Utils::Format("LR      00000000       PC      00000000"), 10, 156);
			screen.DrawSysfont(Utils::Format("Press any other button to shutdown"), 10, 181);
			return true;
		});
	}
	void spoiler(MenuEntry *entry)
	{
		OSD::Run([](const Screen &screen)
		{
			if (!screen.IsTop)
				return false;
			screen.DrawSysfont(Utils::Format("まあ嘘やけど(-ω-)"), 10, 206);
			return true;
		});
	}
}