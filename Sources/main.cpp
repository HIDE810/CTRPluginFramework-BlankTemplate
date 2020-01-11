#include "common.hpp"
#include <vector>

#define PLUGIN_NAME			"MultiFunc3gx"
#define MAJOR_VERSION		1
#define MINER_VERSION		0
#define REVISION_VERSION	0

namespace CTRPluginFramework
{
	const std::string about = u8"If you have any trouble, please contact me.\n\n\n" \
		u8"Twitter: https://twitter.com/HIDE810dev\n" \
		u8"GitHub: https://github.com/HIDE810";
		
	void    InitMenu(PluginMenu &menu)
    {
		std::string name1, name2, note1, note2;
		
		name1 = Color::Yellow << "Fake Error";
		note1 = Color::Red << "Warning:\n\n" << Color::Orange << "This option will cause a fake error.\nSet the error status beforehand.";
		menu += new MenuEntry(name1, nullptr, FakeError, note1);
		
		name2 = Color::SkyBlue << "Information";
		note2 = Color::Yellow << "You can check some information about your console.";
		menu += new MenuEntry(name2, nullptr, Information, note2);
		
		menu += new MenuEntry("Hex Calculator", nullptr, Calculator, "");
		menu += new MenuEntry("Hex to Dec", nullptr, HexToDec, "");
    }
	
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu(PLUGIN_NAME, MAJOR_VERSION, MINER_VERSION, REVISION_VERSION, about);
        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return (0);
    }
}