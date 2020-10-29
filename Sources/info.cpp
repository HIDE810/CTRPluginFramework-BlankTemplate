#include "common.hpp"

#include <time.h>

#include <vector>
#include <sstream>
#include <iomanip>

namespace CTRPluginFramework
{   
    std::string SystemModel()
    {
        u8 model = 0;
        std::stringstream models;
        
        std::vector<std::string> Model = 
        {
            "OLD 3DS",
            "OLD 3DS XL",
            "NEW 3DS",
            "OLD 2DS",
            "NEW 3DS XL",
            "NEW 2DS XL"
        };
        
        CFGU_GetSystemModel(&model);
        models << "Model: " << Model[model];
        return models.str();
    }
    
    std::string SystemRegion()
    {
        u8 region = 0;
        std::stringstream regions;

        std::vector<std::string> Region =
        {
            "Japan",
            "USA",
            "Europe",
            "Australia",
            "China",
            "Korea",
            "Taiwan"
        };
        
        CFGU_SecureInfoGetRegion(&region);
        regions << "Region: " << Region[region];
        return regions.str();
    }
    
    std::string SystemLanguage()
    {
        std::stringstream language;
        LanguageId lang = System::GetSystemLanguage();
        int lang_num = static_cast<int>(lang);
        
        
        std::vector<std::string> Language =
        {
            "Japanese",
            "English",
            "French",
            "German",
            "Italian",
            "Spanish",
            "Simplified Chinese",
            "Korean",
            "Dutch",
            "Portugese",
            "Russian",
            "Traditional Chinese"
        };
        
        language << "Language: " << Language[lang_num];
        return language.str();
    }
    
    std::string TitleID()
    {
        std::stringstream titleid;
        titleid << "TitleID: 0x" << std::setw(16) << std::setfill('0') << std::hex << Process::GetTitleID();
        return titleid.str();
    }
    
    std::string InternetAccess()
    {
        std::stringstream netStatus;
        netStatus << "Wi-Fi: " << (System::IsConnectedToInternet()? "ON" : "OFF");
        return netStatus.str();
    }
    
    std::string CurrentTime()
    {
        std::ostringstream currentTime;
        
        time_t unixTime = time(NULL);
        struct tm* timeStruct = gmtime((const time_t *)&unixTime);

        int hours = timeStruct->tm_hour;
        int minutes = timeStruct->tm_min;
        int seconds = timeStruct->tm_sec;

        currentTime <<  "Time: " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
        
        return currentTime.str();
    }

    void DrawInfo(MenuEntry *entry)
    {   
        OSDManager.Lock();
        const Screen &scr = OSD::GetTopScreen();
        
        scr.DrawRect(30, 20, 340, 200, Color::Black);
        scr.DrawRect(32, 22, 336, 196, Color::White, false);
        scr.DrawRect(41, 41, 120, 1, Color::White);
        scr.DrawSysfont("Information", 41, 25);
        scr.DrawSysfont(SystemModel(), 41, 50);
        scr.DrawSysfont(SystemRegion(), 41, 70);
        scr.DrawSysfont(SystemLanguage(), 41, 90);
        scr.DrawSysfont(TitleID(), 41, 110);
        scr.DrawSysfont(InternetAccess(), 41, 130);
        scr.DrawSysfont(CurrentTime(), 41, 150);
        
        OSDManager.Unlock();
    }

    void DrawRegInfo(MenuEntry *entry)
    {
        CpuRegisters reg;
        
        OSDManager.Lock();
        const Screen &scr = OSD::GetTopScreen();

        u32 dy = 0, i = 0;
        for(const u32 &r : reg.r)
            dy = scr.Draw(Utils::Format("r%-2d  = %08X", i++, r), 0, dy);

        dy = scr.Draw(Utils::Format("sp   = %08X", reg.sp), 0, dy);
        dy = scr.Draw(Utils::Format("lr   = %08X", reg.lr), 0, dy);
        dy = scr.Draw(Utils::Format("pc   = %08X", reg.pc), 0, dy);
        dy = scr.Draw(Utils::Format("cpsr = %08X", reg.cpsr), 0, dy);
        
        OSDManager.Unlock();
    }
    
    void DrawKeyInfo(MenuEntry *entry)
    {
        u32 dy = 0, i = 0;
        
        OSDManager.Lock();
        const Screen &scr = OSD::GetTopScreen();
        
        std::vector<std::string> key_list = {"A", "B", "Select", "Start", "Right", "Left", "Up", "Down", "R", "L", "X", "Y"}; 
        
        for(const std::string &key : key_list)
            dy = scr.Draw(Utils::Format("%-6s : %-3s", key.c_str(), (*(u16*)0x90146000 >> i++) & 1 ? "OFF" : "ON"), 0, dy);
        
        OSDManager.Unlock();
	}
}