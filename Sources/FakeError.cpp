#include "common.hpp"

namespace CTRPluginFramework
{
	static StringVector status;
	int buf;
	std::string Activate, tid;

	static const std::vector<Item> g_status =
	{
		{"Reboot"},
		{"Shutdown"}
	};
	
	void PowerChange(void)
	{
		ptmSysmInit();
		
		Handle serviceHandle = 0;
		Result result = srvGetServiceHandle(&serviceHandle, "ptm:sysm");
		
		if (result != 0) {
            return;
        }

		u32 *commandBuffer = getThreadCommandBuffer();
		commandBuffer[0] = buf;
		commandBuffer[1] = 0x00000000;
		commandBuffer[2] = 0x00000000;
						
		if (buf == 0x040700C0)
			commandBuffer[3] = 0x00000000;

		svcSendSyncRequest(serviceHandle);
		svcCloseHandle(serviceHandle);
		
		ptmSysmExit();
	}
    
    bool DrawErrorMessage(const Screen &screen)
    {
        if (screen.IsTop)
		    return false;
		
		if (!screen.IsTop)
		{
			screen.FlushFramebuffer();
			
			screen.DrawRect(0, 0, 320, 240, Color::Black);
			screen.Draw("An error occurred (ErrDisp)", 10, 10, Color::Red);
			screen.Draw("Error type:       generic", 10, 30);
			screen.Draw("Process ID:       9", 10, 50);
			screen.Draw("Process name:     Fake Error", 10, 60);
			screen.Draw("Process title ID: 0x" << tid, 10, 70);
			screen.Draw("Address:          0x00000000", 10, 90);
			screen.Draw("Error code:       0x00000000", 10, 100);
			screen.Draw("Press A to continue.", 10, 140);
			
			if (Controller::IsKeyDown(A))
				PowerChange();
			
			tid.clear();
		}
		return true;
    }

	void FakeError(MenuEntry *entry)
	{
        bool DrawErrorMessage(const Screen &screen);
        
		if (status.empty())
		{
			for (const Item &i : g_status)
				status.push_back(i.name);
		}
		Keyboard keyboard("Select the error status:", status);
		int choice = keyboard.Open();

		switch (choice){
			case 0:
				buf = 0x04090080;
				break;
			case 1:
				buf = 0x040700C0;
				break;
		}
		
		if (choice != -1)
		{
			entry->Name() = Activate << g_status[choice].name;
			entry->SetGameFunc([](MenuEntry *entry)
			{
				if (entry->IsActivated())
				{
					Process::GetTitleID(tid);
                    OSD::Run(DrawErrorMessage);
				}
                
                if (!entry->IsActivated())
					OSD::Stop(DrawErrorMessage);
			});
		}
	}
}