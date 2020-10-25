#include "common.hpp"

namespace CTRPluginFramework
{
    bool DrawRegInfo(const Screen &scr)
    {
        CpuRegisters reg;
		
		if (scr.IsTop)
        {
            u32 dy = 0, i = 0;
            for(const u32 &r : reg.r)
                dy = scr.Draw(Utils::Format("r%-2d  = %08X", i++, r), 0, dy);
		
            dy = scr.Draw(Utils::Format("sp   = %08X", reg.sp), 0, dy);
            dy = scr.Draw(Utils::Format("lr   = %08X", reg.lr), 0, dy);
            dy = scr.Draw(Utils::Format("pc   = %08X", reg.pc), 0, dy);
            dy = scr.Draw(Utils::Format("cpsr = %08X", reg.cpsr), 0, dy);
        }
        return true;
    }
    
    void DisplayRegisters(MenuEntry *entry)
    {
        bool DrawRegInfo(const Screen &scr);
        entry->IsActivated() ? OSD::Run(DrawRegInfo) : OSD::Stop(DrawRegInfo);
    }
}