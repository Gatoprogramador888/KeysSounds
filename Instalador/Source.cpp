#include <windows.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <strsafe.h>
#include <filesystem>
#include <fstream>
#include <string>

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


    fs::path installPath = fs::path(programFilesPath) / L"KeySoundProject";
    fs::create_directories(installPath);

    // 2️⃣ Copiar bin, assets, config al destino
    fs::path releasePath = fs::current_path().parent_path();
    CopyDirectory(releasePath / L"bin", installPath);
    CopyDirectory(releasePath / L"installer", installPath);

    // 3️⃣ Crear estructura de archivos vacía si faltan
    CreateInstallerStructure(installPath);

    // 4️⃣ Agregar KeySoundHook.exe al inicio
    fs::path keyHookExe = installPath / L"bin\\KeySoundHook.exe";
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
    fs::path editorExe = installPath / L"bin\\KeySoundEditor.exe";

    if (!CreateShortcut(editorExe.c_str(), shortcutPath.c_str(), L"Direct access to KeySoundEditor"))
        MessageBoxA(NULL, "Could not create shortcut.", "Error", MB_OK | MB_ICONERROR);

    MessageBoxA(NULL, "Installation completed successfully!", "Installer", MB_OK | MB_ICONINFORMATION);
    return 0;
}

