#include <Windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

const wchar_t* EVENT_NAME = L"Global\\StopHookEvent";

bool DeleteStartupKey(const wchar_t* entryName) {
    HKEY hKey;
    const LPCWSTR DIRRUN = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    LSTATUS openKey = RegOpenKeyExW(HKEY_CURRENT_USER,
        DIRRUN,
        NULL, KEY_SET_VALUE, &hKey);

    if (openKey == ERROR_SUCCESS)
    {
        LSTATUS deleteKey = RegDeleteValueW(hKey, entryName);
        if (deleteKey == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return true;
        }
        RegCloseKey(hKey);
    }
    return false;
}

bool DeleteFolderRecursively(const fs::path& folderPath) {
    std::error_code errorCode;
    fs::remove_all(folderPath, errorCode);
    return !errorCode;
}

bool NotifyAppToStop(const wchar_t* eventName)
{
    // Abrir un handle al evento existente para modificar su estado
    HANDLE hStopEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, eventName);
    if (hStopEvent == NULL)
    {
        DWORD err = GetLastError();
        if (err == ERROR_FILE_NOT_FOUND)
        {
            std::wcout << L"The event doesn't exist. The app is probably already closed.\n";
        }
        else
        {
            std::wcout << L"The event could not be opened. Error: " << err << L"\n";
        }
        return false;
    }

    // Señalizar el evento para avisar a la aplicación que debe detenerse
    if (!SetEvent(hStopEvent))
    {
        std::wcout << L"The event could not be signaled.\n";
        CloseHandle(hStopEvent);
        return false;
    }

    // Cerrar el handle
    CloseHandle(hStopEvent);
    std::wcout << L"Event correctly signaled.\n";
    return true;
}


int main() {
    //1. Terminate hook task if on
    if (NotifyAppToStop(EVENT_NAME))
    {
        std::wcout << L"The application was notified to close.\n";
    }
    else
    {
        std::wcout << L"The application could not be notified.\n";
    }

    // 2. Remove the start key
    std::wstring appName = L"KeySoundHook.exe";
    if (DeleteStartupKey(appName.c_str()))
        std::wcout << L"Start key removed\n";
    else
        std::wcout << L"Could not delete startup key\n";

    // 3. Delete folders
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    fs::path mainFolder = std::filesystem::path(path).parent_path();
    fs::path folderMusic = mainFolder / "Music";

    if (DeleteFolderRecursively(folderMusic))
        std::wcout << L"Music folder deleted";
    else
        std::wcout << L"Could not delete Music Folder\n";

    if (DeleteFolderRecursively(mainFolder))
        std::wcout << L"Music folder deleted\n";
    else
        std::wcout << L"Could not delete parent folder\n";

    return 0;
}