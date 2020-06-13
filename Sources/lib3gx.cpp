#include "lib3gx.hpp"

#include <time.h>

#include <vector>
#include <sstream>
#include <iomanip>

//#define PhysAddr(addr) (u32 *)(addr + 0x80000000)

namespace CTRPluginFramework
{
    /*
    void Flash(bool top, bool bottom, u32 color)
    {
        //https://www.3dbrew.org/wiki/LCD_Registers
        u32 *top_flash = PhysAddr(0x10202204);
        u32 *bottom_flash = PhysAddr(0x10202A04);
        
        color += 0x1000000;
        
        *top_flash = top? color : 0;
        *bottom_flash = bottom? color : 0;
    }
    
    void DumpHash(const std::string &path)
    {
        u64 hash = 0;
        CFGU_GenHashConsoleUnique(0, &hash);
        File file;
        File::Open(file, path, File::RWC);
        file.WriteLine(std::to_string(hash));
        file.Close();
    }
    
    std::string SystemModel(void)
    {
        u8 model = 0;
        
        std::vector<std::string> Model = 
        {
            "OLD 3DS",
            "OLD 3DS XL",
            "NEW 3DS",
            "OLD 2DS",
            "NEW 3DS XL"
        };
        
        CFGU_GetSystemModel(&model);
        return Model[model];
    }
    
    std::string SystemRegion(void)
    {
        u8 region = 0;

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
        return Region[region];
    }
    
    std::string SystemLanguage(void)
    {
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
        
        return Language[lang_num];
    }
    
    std::string CurrentTime(void)
    {
        std::ostringstream currentTime;
        
        time_t unixTime = time(NULL);
        struct tm* timeStruct = gmtime((const time_t *)&unixTime);

        int hours = timeStruct->tm_hour;
        int minutes = timeStruct->tm_min;
        int seconds = timeStruct->tm_sec;

        currentTime << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
        
        return currentTime.str();
    }*/
}