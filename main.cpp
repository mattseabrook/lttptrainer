#include <iostream>
#include <string>
#include <string_view>

#ifdef _WIN32
#include <Windows.h>
#include <TlHelp32.h>
#endif

#ifdef __linux__
#include <filesystem>
#endif

bool isProcessRunning(const std::wstring& processName)
{
#ifdef _WIN32
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (processName == entry.szExeFile)
            {
                CloseHandle(snapshot);
                return true;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
#endif

#ifdef __linux__
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("/proc"))
    {
        if (!entry.is_directory())
            continue;

        const std::string& path = entry.path().string();

        // Check if path is a PID by confirming it's a number
        if (std::all_of(path.begin(), path.end(), ::isdigit))
        {
            try
            {
                std::ifstream cmdline(path + "/cmdline");
                std::string cmd;
                std::getline(cmdline, cmd);
                if (!cmd.empty() && cmd.find(processName) != std::string::npos)
                    return true;
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                // Handle any potential exception here, if needed
            }
        }
    }
#endif

    return false;
}

int main()
{
#ifdef _WIN32
    system("cls");
#endif

    constexpr std::string_view art = R"(
              _______
          ..-'`       ````---.
      .'          ___ .'````.'SS'.
      /        ..-SS####'.  /SSHH##'.
      |       .'SSSHHHH##|/#/#HH#H####'.
      /      .'SSHHHHH####/||#/: \SHH#####\
      /      /SSHHHHH#####/!||;`___|SSHH###\
      -..__    /SSSHHH######.         \SSSHH###\
      `.'-.''--._SHHH#####.'           '.SH####/
      '. ``'-  '/SH####`/_             `|H##/
      | '.     /SSHH###|`'==.       .=='/\H|
      |   `'-.|SHHHH##/\__\/        /\//|~|/
      |    |S#|/HHH##/             |``  |
      |    \H' |H#.'`              \    |
      |        ''`|               -     /
      |          /H\          .----    /
      |         |H#/'.           `    /
      |          \| | '..            /
      |            /|    ''..______.'
      \          //\__    _..-. | 
          \         ||   ````     \ |_
          \    _.-|               \| |_
          _\_.-'   `'''''-.        |   `--.
      ''``    \            `''-;    \ /
              \      .-'|     ````.' -
              |    .'  `--'''''-.. |/
              |  .'               \|
              |.'
)";

    constexpr std::string_view details = R"(
    lttptrainer
    v.0.2 - 2023-9-15

    Author: Matt Seabrook (info@mattseabrook.net)
)";

    std::cout << details << art << std::endl;

#ifdef _WIN32
    if (isProcessRunning(L"snes9x-x64.exe"))
    {
        std::cout << "Running" << std::endl;
    }
    else
    {
        std::cout << "Not Running" << std::endl;
    }
#endif

#ifdef __linux__
    if (isProcessRunning("snes9x-x64.exe"))
    {
        std::cout << "Running" << std::endl;
    }
    else
    {
        std::cout << "Not Running" << std::endl;
    }
#endif

    return 0;
}
