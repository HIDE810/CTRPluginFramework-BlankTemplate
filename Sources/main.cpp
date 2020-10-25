#include "common.hpp"

#define PLUGIN_NAME         "MultiFunc3gx"
#define MAJOR_VERSION       2
#define MINER_VERSION       5
#define REVISION_VERSION    0

namespace CTRPluginFramework
{
    const std::string about = u8"If you have any trouble, please contact me.\n\n\n" \
        u8"Twitter: https://twitter.com/HIDE810dev\n" \
        u8"GitHub: https://github.com/HIDE810";

	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey)
    {
        if (entry != nullptr)
        {
            entry->Hotkeys += hotkey;
            entry->SetArg(new std::string(entry->Name()));
            entry->Name() += " " + hotkey.ToString();
            entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index)
            {
                std::string *name = reinterpret_cast<std::string *>(entry->GetArg());

                entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
            });
        }
		return (entry);
    }
	
	void    InitMenu(PluginMenu &menu)
    {
        menu += new MenuFolder("Hex", "",
        {
            new MenuEntry("Hex calculator", nullptr, Calculator),
            new MenuEntry("Hex to Dec", nullptr, HexToDec)
        });
        
        menu += new MenuFolder("Flash", "",
        {
            EntryWithHotkey(new MenuEntry("Random flash", RandomFlash), Hotkey(Key::X, "Random Flash")),
            new MenuEntry("Touch flash", TouchFlash)
        });
        
        menu += new MenuFolder("Service test", "",
        {
            new MenuEntry("Force power button (ID:0x202)", ForcePowerButton),
            new MenuEntry("Shutdown (ID:0x203)", Shutdown),
            new MenuEntry("Force HOME button (ID:0x204)", ForceHomeButton)
        });
        
        menu += new MenuEntry("Change screen brightness", nullptr, ChangeBrightness);
        menu += new MenuEntry("Fake error", nullptr, FakeError);
        menu += new MenuEntry("Hash Dumper", nullptr, HashDumper);
        menu += new MenuEntry("Information", Information);
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