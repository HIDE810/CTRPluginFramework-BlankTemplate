#pragma once

#include "3ds.h"
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    /**
    * \brief Display a flash
    * \param top Whether to display the flash on the top screen
    * \param bottom Whether to display the flash on the bottom screen
    * \param color The color of the flash
    */
	void Flash(bool top, bool bottom, u32 color = 0);
    
    /**
    * \brief Dump a console-unique hash
    * \param path The path of the file to dump
    */
    void DumpHash(const std::string &path);
    
    /**
    * \brief Get the system model
    * \return An std::string with the name of the system model
    */
    std::string SystemModel(void);
    
    /**
    * \brief Get the system region
    * \return An std::string with the system region
    */
    std::string SystemRegion(void);
    
    /**
    * \brief Get the system language
    * \return An std::string with the system language
    */
    std::string SystemLanguage(void);
    
    /**
    * \brief Get the current time
    * \return An std::string with the current time
    */
    std::string CurrentTime(void);
}