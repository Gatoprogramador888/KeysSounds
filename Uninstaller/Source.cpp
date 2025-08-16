#include <Windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <strsafe.h>
#include <ShlObj.h>
#include <knownfolders.h>
#include <tlhelp32.h>

namespace fs = std::filesystem;

const wchar_t* EVENT_NAME = L"Global\\StopHookEvent";

// Eliminar la clave de inicio
bool DeleteStartupKey(const wchar_t* entryName) {
    HKEY hKey;
    const LPCWSTR DIRRUN = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    LSTATUS openKey = RegOpenKeyExW(HKEY_CURRENT_USER,
        DIRRUN,
        NULL, KEY_SET_VALUE, &hKey);

    if (openKey == ERROR_SUCCESS) {
        LSTATUS deleteKey = RegDeleteValueW(hKey, entryName);
        RegCloseKey(hKey);
        return deleteKey == ERROR_SUCCESS;
    }
    return false;
}

// Eliminar una carpeta de manera recursiva
bool DeleteFolderRecursively(const fs::path& folderPath) {
    std::error_code errorCode;
    fs::remove_all(folderPath, errorCode);
    return !errorCode;
}

// Señalizar a la aplicación para que cierre
/*bool NotifyAppToStop(const wchar_t* eventName) {
    HANDLE hStopEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, eventName);
    if (!hStopEvent) return false;
    SetEvent(hStopEvent);
    CloseHandle(hStopEvent);
    return true;
}*/

void KillProcessByName(const wchar_t* name) {
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

// Eliminar acceso directo
bool DeleteShortcut(const fs::path& shortcutPath) {
    std::error_code ec;
    return fs::remove(shortcutPath, ec);
}

int main() {
    std::string decision;
    std::cout << "Do you want to continue with the uninstallation? (y/n)\n";
    std::cin >> decision;
    if (decision != "y" && decision != "Y") {
        std::cout << "Closing uninstaller\n";
        return 0;
    }

    // 3. Obtener carpeta principal del programa
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    fs::path mainFolder = fs::path(path).parent_path();
    fs::path ant = fs::path("..");

    // 4. Carpetas según diagrama
    fs::path folderBin = mainFolder /  ant / L"bin";
    fs::path folderAssets = mainFolder / ant / L"assets";
    fs::path folderConfig = mainFolder /  ant / L"config";
    fs::path folderInstaller = mainFolder / L"installer";

    KillProcessByName(L"KeySoundHook.exe");
    KillProcessByName(L"KeySoundEditor.exe");

    const int sleep = 1000;
    Sleep(sleep);

    // 2. Eliminar la clave de inicio
    if (DeleteStartupKey(L"KeySoundHook"))
        std::wcout << L"Startup key removed\n";
    else
        std::wcout << L"Startup key not found or could not delete\n";

    Sleep(sleep);
    // 5. Eliminar carpetas
    DeleteFolderRecursively(folderBin);
    DeleteFolderRecursively(folderAssets);
    DeleteFolderRecursively(folderConfig);
    DeleteFolderRecursively(folderInstaller);

    Sleep(sleep);
    // 6. Eliminar posibles accesos directos del escritorio
    wchar_t desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        DeleteShortcut(fs::path(desktopPath) / L"KeySoundEditor.lnk");
    }

    std::wcout << L"Uninstallation completed. Press any key to exit.\n";
    std::cin.ignore();
    std::cin.get();

    std::wcout << L"Press any key to finish the uninstallation.\n";

    return 0;
}
