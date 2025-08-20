#include <windows.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <strsafe.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

// ------------------- Función para agregar al startup -------------------
bool AddToStartup(const std::wstring& appName, const std::wstring& appPath)
{
    HKEY hKey;
    const LPCWSTR DIRRUN = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, DIRRUN, 0, KEY_WRITE, &hKey);
    if (result != ERROR_SUCCESS) return false;

    result = RegSetValueExW(hKey, appName.c_str(), 0, REG_SZ,
        (const BYTE*)appPath.c_str(),
        static_cast<DWORD>((appPath.size() + 1) * sizeof(wchar_t)));

    RegCloseKey(hKey);
    return result == ERROR_SUCCESS;
}

// ------------------- Función para crear acceso directo -------------------
bool CreateShortcut(LPCWSTR targetPath, LPCWSTR shortcutPath, LPCWSTR description)
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return false;

    IShellLinkW* pShellLink = nullptr;
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
        IID_IShellLinkW, (LPVOID*)&pShellLink);
    if (FAILED(hr)) { CoUninitialize(); return false; }

    pShellLink->SetPath(targetPath);
    pShellLink->SetDescription(description);

    IPersistFile* pPersistFile = nullptr;
    hr = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
    if (SUCCEEDED(hr))
    {
        hr = pPersistFile->Save(shortcutPath, TRUE);
        pPersistFile->Release();
    }

    pShellLink->Release();
    CoUninitialize();
    return SUCCEEDED(hr);
}

// ------------------- Función para copiar carpetas recursivamente -------------------
void CopyDirectory(const fs::path& source, const fs::path& destination)
{
    fs::create_directories(destination);
    for (auto& entry : fs::recursive_directory_iterator(source))
    {
        const auto& path = entry.path();
        auto relative = fs::relative(path, source);
        fs::path target = destination / relative;

        if (fs::is_directory(path))
            fs::create_directories(target);
        else if (fs::is_regular_file(path))
            fs::copy_file(path, target, fs::copy_options::overwrite_existing);
    }
}

// ------------------- Función para crear estructura de config vacía -------------------
void CreateInstallerStructure(const fs::path& basePath)
{
    try {
        fs::path assetsMusic = basePath / L"assets" / L"music";
        fs::path configSettings = basePath / L"config" / L"settings";
        fs::path configMusic = basePath / L"config" / L"music";

        fs::create_directories(assetsMusic);
        fs::create_directories(configSettings);
        fs::create_directories(configMusic);

        fs::path musicDirFile = configMusic / L"Music_Directory.txt";
        fs::path settingsFile = configSettings / L"Settings.txt";
        fs::path mainConfigFile = configSettings / L"MainConfiguration.txt";

        std::wofstream(musicDirFile) << L"";
        std::wofstream(settingsFile) << L"Music_Directory\n";
        std::wofstream(mainConfigFile) << L"Music_Directory\n";
    }
    catch (const fs::filesystem_error& e)
    {
        MessageBoxA(NULL, e.what(), "Filesystem Error", MB_OK | MB_ICONERROR);
    }
}

// ------------------- Main -------------------
int main()
{
    // 1️⃣ Carpeta de destino en Program Files
    wchar_t programFilesPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES, NULL, 0, programFilesPath)))
    {
        MessageBoxA(NULL, "Cannot get Program Files path.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    std::wstring bin = L"bin", installer = L"installer";
    fs::path installPath = fs::path(programFilesPath) / L"KeySoundProject";
    fs::path iBinPath = installPath / bin;
    fs::path iInstallerPath = installPath / installer;

    fs::create_directories(installPath);
    fs::create_directories(iBinPath);
    fs::create_directories(iInstallerPath);

    // 2️⃣ Copiar bin, assets, config al destino
    fs::path releasePath = fs::current_path().parent_path();
    fs::path rBinPath = releasePath / bin;
    fs::path rInstallerPath = releasePath / installer;

    CopyDirectory(rBinPath, iBinPath);
    CopyDirectory(rInstallerPath, iInstallerPath);

    // 3️⃣ Crear estructura de archivos vacía si faltan
    CreateInstallerStructure(installPath);

    // 4️⃣ Agregar KeySoundHook.exe al inicio
    fs::path keyHookExe = iBinPath / L"KeySoundHook.exe";
    if (!AddToStartup(L"KeySoundHook", keyHookExe.wstring()))
        MessageBoxW(NULL, L"Could not add KeySoundHook to startup", L"Error", MB_OK | MB_ICONERROR);

    // 5️⃣ Crear acceso directo en escritorio para KeySoundEditor.exe
    wchar_t desktopPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath)))
    {
        MessageBoxA(NULL, "Could not get desktop path.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    fs::path shortcutPath = fs::path(desktopPath) / L"KeySoundEditor.lnk";
    fs::path editorExe = iBinPath / L"KeySoundEditor.exe";

    if (!CreateShortcut(editorExe.c_str(), shortcutPath.c_str(), L"Direct access to KeySoundEditor"))
        MessageBoxA(NULL, "Could not create shortcut.", "Error", MB_OK | MB_ICONERROR);

    MessageBoxA(NULL, "Installation completed successfully!", "Installer", MB_OK | MB_ICONINFORMATION);

    //Borrar el installer actual
    fs::path currentInstallerFolder = fs::current_path();

    // Nombres de las carpetas a eliminar alrededor del instalador
    std::vector<fs::path> foldersToDelete = {
        currentInstallerFolder.parent_path() / L"bin",
        currentInstallerFolder
    };

    // Crear batch temporal
    wchar_t tempPath[MAX_PATH];
    GetTempPathW(MAX_PATH, tempPath);
    fs::path batFile = fs::path(tempPath) / L"deleteProject.bat";
    std::cout << "Erasing in " << batFile << std::endl;
    std::wofstream bat(batFile);

    // Cabecera
    bat << L"@echo off\n";
    bat << L"ping 127.0.0.1 -n 2 > nul\n"; // espera ~2 seg

    // Agregar cada carpeta para borrarla
    for (auto& folder : foldersToDelete)
    {
        std::cout << "Erasing in " << folder << std::endl;
        bat << L"rmdir /s /q \"" << folder.wstring() << L"\"\n";
    }

    // Finalmente borrar la carpeta del instalador y el propio batch
    bat << L"rmdir /s /q \"" << currentInstallerFolder.parent_path().wstring() << L"\"\n";
    std::cout << "Erasing in " << currentInstallerFolder.parent_path() << std::endl;
    bat << L"del \"%~f0\"\n"; // se borra a sí mismo
    bat.close();
    std::cin.ignore();

    // Ejecutar el batch de forma oculta
    ShellExecuteW(NULL, L"open", batFile.c_str(), NULL, NULL, SW_HIDE);

    return 0;
}

