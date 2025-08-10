#include <windows.h>
#include <string>
#include <fstream>
#include <filesystem>


namespace fs = std::filesystem;

bool AddToStartup(const std::wstring& appName, const std::wstring& appPath)
{
    HKEY hKey;
    const LPCWSTR DIRRUN = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LONG result = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        DIRRUN,
        NULL,
        KEY_WRITE,
        &hKey
    );

    if (result != ERROR_SUCCESS)
        return false;

    result = RegSetValueExW(
        hKey,
        appName.c_str(),
        0,
        REG_SZ,
        (const BYTE*)appPath.c_str(),
        (DWORD)((appPath.size() + 1) * sizeof(wchar_t))
    );

    RegCloseKey(hKey);
    return result == ERROR_SUCCESS;
}

void CreateFileMusic()
{
    std::filesystem::path pathOrigin = fs::current_path();
    std::filesystem::path pathFile = pathOrigin / "Music_Directory.txt";
    std::filesystem::path pathMusic = pathOrigin / "Music";
    std::wofstream file(pathFile);
    try {
        if (!fs::exists(pathMusic) || !fs::is_directory(pathMusic)) {
            MessageBoxW(NULL, L"The directory does not exist or is invalid", L"Error", MB_OK | MB_ICONERROR);
            return;
        }

        for (const auto& entry : fs::directory_iterator(pathMusic)) {
            if (fs::is_regular_file(entry.path())) {
                file << entry.path().filename().wstring() << L"\n";
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        MessageBox(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
    }
}

int main()
{
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);

    if (AddToStartup(L"KeySoundHook", path))
        MessageBoxW(NULL, L"Added to start", L"OK", MB_OK);
    else
        MessageBoxW(NULL, L"Could not add to start", L"Error", MB_OK | MB_ICONERROR);

    CreateFileMusic();

    return 0;
}
