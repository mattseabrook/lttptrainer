// main.cpp

#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

int main()
{
	// Get the process ID:
	DWORD pid;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, L"snes9x-x64.exe") == 0)
			{
				pid = entry.th32ProcessID;

				// Get a handle to the process:
				HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

				// Get the CPU usage:
				FILETIME creationTime, exitTime, kernelTime, userTime;
				GetProcessTimes(process, &creationTime, &exitTime, &kernelTime, &userTime);
				ULARGE_INTEGER kernelTimeInt, userTimeInt;
				kernelTimeInt.HighPart = kernelTime.dwHighDateTime;
				kernelTimeInt.LowPart = kernelTime.dwLowDateTime;
				userTimeInt.HighPart = userTime.dwHighDateTime;
				userTimeInt.LowPart = userTime.dwLowDateTime;
				ULARGE_INTEGER totalTimeInt;
				totalTimeInt.QuadPart = kernelTimeInt.QuadPart + userTimeInt.QuadPart;
				double totalTime = totalTimeInt.QuadPart / 10000000.0;

				// Get the memory usage:
				PROCESS_MEMORY_COUNTERS_EX pmc;
				GetProcessMemoryInfo(process, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
				SIZE_T memoryUsage = pmc.PrivateUsage;

				// Output the results:
				std::cout << "Process ID: " << pid << std::endl;
				std::cout << "CPU usage: " << totalTime << " seconds" << std::endl;
				std::cout << "Memory usage: " << memoryUsage << " bytes" << std::endl;

				// Close the handle to the process:
				CloseHandle(process);

				break;
			}
			else {
				std::cout << "snes9x-x64.exe is not running!" << std::endl;
				return 1;
			}
		}
	}

	CloseHandle(snapshot);

	return 0;
}