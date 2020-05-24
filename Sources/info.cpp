#include "common.hpp"

#include <time.h>

#include <vector>
#include <sstream>
#include <iomanip>

namespace CTRPluginFramework
{
    int ret;
    std::string titleid;
    
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
        
        ret = CFGU_GetSystemModel(&model);
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
        
        ret = CFGU_SecureInfoGetRegion(&region);
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

    bool DrawInformation(const Screen &screen)
    {
        if (screen.IsTop)
        {
            screen.DrawRect(30, 20, 340, 200, Color::Black);
            screen.DrawRect(32, 22, 336, 196, Color::White, false);
            screen.DrawRect(41, 41, 120, 1, Color::White);
            screen.DrawSysfont("Information", 41, 25);
            screen.DrawSysfont(SystemModel(), 41, 50);
            screen.DrawSysfont(SystemRegion(), 41, 70);
            screen.DrawSysfont(SystemLanguage(), 41, 90);
            screen.DrawSysfont("TitleID: " << titleid, 41, 110);
            screen.DrawSysfont(InternetAccess(), 41, 130);
            screen.DrawSysfont(CurrentTime(), 41, 150);
            
            titleid.clear();
        }
        return true;
    }

    void Information(MenuEntry *entry)
    {
        bool DrawInformation(const Screen &screen);
        
        if (entry->IsActivated())
        {
            Process::GetTitleID(titleid);
            OSD::Run(DrawInformation);
        }
        
        if (!entry->IsActivated())
            OSD::Stop(DrawInformation);
    }
}