#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	using StringVector = std::vector<std::string>;
	static StringVector status;

	struct Status
	{
		const char *name;
	};

	static const std::vector<Status> g_status =
	{
		{"Reboot"},
		{"Shutdown"}
	};

	void FakeError(MenuEntry *entry)
	{
		if (status.empty())
		{
			for (const Status &i : g_status)
				status.push_back(i.name);
		}
		Keyboard keyboard("Select the error status.", status);
		int choice = keyboard.Open();
		
		if (choice != -1) {
			entry->Name() = g_status[choice].name;
		}
		else entry->Name() = "Unknown error";
		
		entry->SetGameFunc([](MenuEntry *entry)
		{
			if (entry->IsActivated())
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
					screen.DrawSysfont(Utils::Format("Press any other button to continue"), 10, 181);
					/*
					if (Controller::GetKeysDown())
					{
						Handle serviceHandle = 0;
						Result result = srvGetServiceHandle(&serviceHandle, "ptm:sysm");

						u32 *commandBuffer = getThreadCommandBuffer();
						commandBuffer[0] = ;
						commandBuffer[1] = 0x00000000;
						commandBuffer[2] = 0x00000000;
						commandBuffer[3] = 0x00000000;

						svcSendSyncRequest(serviceHandle);
						svcCloseHandle(serviceHandle);
					}*/
					return true;
				});
			}
		});
	}
}
