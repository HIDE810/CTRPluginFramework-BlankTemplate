#include "common.hpp"

namespace CTRPluginFramework
{
    int *p = (int *)0x90202204;
    
    void RandomFlash(MenuEntry *entry)
    {
        if (entry->Hotkeys[0].IsDown())
        {
            *p = Utils::Random(0, 0xFFFFFF) + 0x1000000;

            //Sleep thread for 1.0s
            svcSleepThread(1000000000);
        }
        else *p = 0;
    }

    void TouchFlash(MenuEntry *entry)
    {
        touchPosition tp;
        hidTouchRead(&tp);
        
        u32 color = (0xFFFFFF/76800) * tp.px * tp.py + 0x1000000;

        *p = Controller::IsKeyDown(Touchpad)? color : 0;

        //Sleep thread for 0.1s
        svcSleepThread(100000000);
    }
}