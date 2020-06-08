#include "common.hpp"

namespace CTRPluginFramework
{
    void ForcePowerButton(MenuEntry *entry)
    {
        srvPublishToSubscriber(0x202, 0);
    }
    
    void ForceHomeButton(MenuEntry *entry)
    {
        srvPublishToSubscriber(0x204, 0);
    }
    
    void Shutdown(MenuEntry *entry)
    {
        srvPublishToSubscriber(0x203, 0);
    }
}