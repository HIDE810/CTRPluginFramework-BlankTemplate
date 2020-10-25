#ifndef COMMON_HPP
#define COMMON_HPP

#include "3ds.h"
#include "csvc.h"
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
    
    struct Item
    {
        const char *name;
    };
    
    void FakeError(MenuEntry *entry);
    void Information(MenuEntry *entry);
    void Calculator(MenuEntry *entry);
    void HexToDec(MenuEntry *entry);
    void RandomFlash(MenuEntry *entry);
    void TouchFlash(MenuEntry *entry);
    void ChangeBrightness(MenuEntry *entry);
    void HashDumper(MenuEntry *entry);
    void ForcePowerButton(MenuEntry *entry);
    void Shutdown(MenuEntry *entry);
    void ForceHomeButton(MenuEntry *entry);
}

#endif