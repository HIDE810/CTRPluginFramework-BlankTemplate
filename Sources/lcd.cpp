#include "common.hpp"

//Where physaddr base is 0x80000000.
#define PhysAddr(addr) (u32 *)(addr + 0x80000000)

namespace CTRPluginFramework
{
    int level = 0;
    
    //https://www.3dbrew.org/wiki/LCD_Registers
    u32 *top_flash = PhysAddr(0x10202204);
    u32 *top_backlight = PhysAddr(0x10202240);
    u32 *bottom_flash = PhysAddr(0x10202A04);
    u32 *bottom_backlight = PhysAddr(0x10202A40);
    
    void Flash(u32 color)
    {
        //Enable flash
        color += 0x1000000;
        
        *top_flash = color;
        *bottom_flash = color;
    }
    
    void RandomFlash(MenuEntry *entry)
    {
        if (entry->Hotkeys[0].IsDown())
        {
            Flash(Utils::Random(0, 0xFFFFFF));

            //Sleep thread for 1.0s
            svcSleepThread(1000000000);
        }
        else
        {
            *top_flash = 0;
            *bottom_flash = 0;
        }
    }

    void TouchFlash(MenuEntry *entry)
    {
        touchPosition tp;
        hidTouchRead(&tp);
        
        u32 pos = (0xFFFFFF/76800) * tp.px * tp.py;

        if(Controller::IsKeyDown(Touchpad))
        {
            Flash(pos);
            
            //Sleep thread for 0.1s
            svcSleepThread(100000000);
        }
        else
        {
            *top_flash = 0;
            *bottom_flash = 0;
        }
    }
    
    void Backlight(void)
    {
        u32 brightness[4] = {0x26, 0x39, 0x4C, 0x5F};
                
        *top_backlight = brightness[level];
        *bottom_backlight = brightness[level];
    }
    
    void ChangeBrightness(MenuEntry *entry)
    {
        static StringVector brightLevel;
        std::string changedTitle = "Brightness level: ";
        
        static const std::vector<Item> g_brightLevel =
        {
            {"1"},
            {"2"},
            {"3"},
            {"4"}
        };
        
        if (brightLevel.empty())
        {
            for (const Item &i : g_brightLevel)
                brightLevel.push_back(i.name);
        }
        Keyboard keyboard("Screen brightness:", brightLevel);
        level = keyboard.Open();

        if(level != -1)
        {
            entry->Name() = changedTitle << g_brightLevel[level].name;
            entry->SetGameFunc([](MenuEntry *entry) {
                Backlight();
            });
        }
    }
}