#include <Windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <ShlObj.h>
#include "Process.h"

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
void DeleteFolderRecursively(const fs::path& folderPath) {
    std::error_code errorCode;
    fs::remove_all(folderPath, errorCode);
    if (errorCode)
    {
        std::cout << "The folder " << folderPath << " could not be deleted\n";
    }
}

void DeleteFolderInstaller(const fs::path folderPath)
{
    std::error_code errorCode;
    for (const auto& file : fs::directory_iterator(folderPath))
    {
        fs::remove(file, errorCode);
        if (errorCode)
        {
            std::cout << "The file " << folderPath << " could not be deleted\n";
        }
    }
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
    //fs::path ant = fs::path("..");

    // 4. Carpetas según diagrama
    fs::path folderBin = mainFolder.parent_path() / L"bin";
    fs::path folderAssets = mainFolder.parent_path() / L"assets";
    fs::path folderConfig = mainFolder.parent_path() / L"config";
    //fs::path folderInstaller = mainFolder;// / L"installer";

    Process::KillProcessByName(KEYSOUNDHOOK);
    Process::KillProcessByName(KEYSOUNDEDITOR);

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
    DeleteFolderInstaller(mainFolder);

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
    

    //Eliminar los restos
    // Carpeta principal KeySoundProject
    fs::path projectFolder = mainFolder.parent_path(); // ajusta según la estructura
    fs::path installerFolder = mainFolder;

    // Crear batch temporal para borrar todo
    wchar_t tempPath[MAX_PATH];
    GetTempPathW(MAX_PATH, tempPath);
    fs::path batFile = fs::path(tempPath) / L"deleteProject.bat";
    std::cout << "Erasing in " << batFile << std::endl;
    std::cout << "Erasing in " << mainFolder << std::endl;
    std::cout << "Erasing in " << projectFolder << std::endl;
    std::wofstream bat(batFile);

    bat << L"@echo off\n";
    //bat << L":loop\n";
    //bat << L"tasklist | findstr /i \"Uninstaller.exe\" > nul\n";
    //bat << L"if %errorlevel%==0 (\n";
    //bat << L"    ping 127.0.0.1 -n 2 > nul\n"; 
    //bat << L"    goto loop\n";
    //bat << L")\n";
    //bat << L":check\n";
    //bat << L"rmdir /s /q \"" << projectFolder.wstring() << L"\"\n";
    //bat << L"if exist \"" << projectFolder.wstring() << L"\" (\n";
    bat << L"    ping 127.0.0.1 -n 5 > nul\n";
    bat << L"rmdir /s /q \"" << projectFolder.wstring() << L"\"\n";
    //bat << L"    goto check\n";
    //bat << L")\n";
    bat << L"del \"%~f0\"\n";
    bat.close();
    MessageBoxA(NULL, "Please close the window where the project is located", "Info", MB_OK | MB_ICONINFORMATION);
    // Ejecutar batch de forma oculta
    ShellExecuteW(NULL, L"runas", batFile.c_str(), NULL, NULL, SW_HIDE);
    return 0;
}
