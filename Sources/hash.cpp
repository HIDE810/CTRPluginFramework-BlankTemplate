#include "common.hpp"

namespace CTRPluginFramework
{
    void HashDumper(MenuEntry *entry)
    {
        u64 hash = 0;
        CFGU_GenHashConsoleUnique(0, &hash);
        File file;
        File::Open(file, "/hash.txt", File::RWC);
        file.WriteLine(std::to_string(hash));
        file.Close();
        (MessageBox("Dumped to 'SD://hash.txt'."))();
    }
}