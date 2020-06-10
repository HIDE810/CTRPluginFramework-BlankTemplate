#include "common.hpp"

namespace CTRPluginFramework
{
    //https://www.3dbrew.org/wiki/Memory_layout
    u32 physaddr = 0x80000000;
 
    //https://www.3dbrew.org/wiki/LCD_Registers
    u32 *top = (u32 *)(physaddr + 0x10202204);
    u32 *bottom = (u32 *)(physaddr + 0x10202A04);
    
    void Flash(u32 color)
    {
        //Flash flag
        u32 enableFlash = 0x1000000;
        
        *top = enableFlash + color;
        *bottom = enableFlash + color;
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
            *top = 0;
            *bottom = 0;
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
            *top = 0;
            *bottom = 0;
        }
    }
}