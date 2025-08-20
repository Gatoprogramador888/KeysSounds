#include "pch.h"
#include <Windows.h>
#include <tlhelp32.h>
#include "Process.h"

std::string Process::WcharPToString(const wchar_t* text)
{
    size_t size = wcslen(text);
    if (size == static_cast<size_t>(-1)) {
        return {}; // conversión fallida
    }
    
    std::string result(size, '\0');
    size_t convertedChars = 0;
    errno_t err = wcstombs_s(&convertedChars, &result[0], result.size() + 1, text, size);

    if (err != 0) {
        return {};
    }

    return result;
}

void Process::KillProcessByName(const wchar_t* name)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, name) == 0) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProc) {
                    TerminateProcess(hProc, 0);
                    CloseHandle(hProc);
                }
            }
        } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);
}

void Process::StartProcessByName(const wchar_t* name)
{
    std::string exe = WcharPToString(name);
    system(exe.c_str());
}
