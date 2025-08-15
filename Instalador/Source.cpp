//winapi
#include <windows.h>
#include <shobjidl.h>
#include <shlguid.h>
#include <objbase.h>
#include <strsafe.h>
#include <ShlObj_core.h>
//librerias estandar
#include <string>
#include <fstream>
#include <filesystem>

//#pragma comment(lib, "ole32.lib")
//#pragma comment(lib, "shell32.lib")


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

void CreateInstallerStructure()
{
    try {
        fs::path pathOrigin = fs::current_path();

        // Carpetas principales
        fs::path pathAssetsMusic = pathOrigin / L"assets" / L"music";
        fs::path pathConfigSettings = pathOrigin / L"config" / L"settings";
        fs::path pathConfigMusic = pathOrigin / L"config" / L"music";

        // Crear carpetas
        fs::create_directories(pathAssetsMusic);
        fs::create_directories(pathConfigSettings);
        fs::create_directories(pathConfigMusic);

        // Archivos necesarios
        fs::path musicDirectoryFile = pathConfigMusic / L"Music_Directory.txt";
        fs::path settingsFile = pathConfigSettings / L"Settings.txt";
        fs::path mainConfigFile = pathConfigSettings / L"MainConfiguration.txt";

        // Crear Music_Directory.txt vacío si no existe
        if (!fs::exists(musicDirectoryFile))
        {
            std::wofstream file(musicDirectoryFile);
            file << L""; // Inicial vacío
        }

        // Escribir "Music_Directory" en Settings.txt y MainConfiguration.txt
        {
            std::wofstream settings(settingsFile);
            settings << L"Music_Directory\n";
        }
        {
            std::wofstream mainConfig(mainConfigFile);
            mainConfig << L"Music_Directory\n";
        }

    }
    catch (const fs::filesystem_error& e) {
        MessageBoxA(NULL, e.what(), "Filesystem Error", MB_OK | MB_ICONERROR);
    }
}


bool CrearAcessoDirectoDelEditor(LPCWSTR rutaObjeto, LPCWSTR rutaAccesoDirecto, LPCWSTR descripcion)
{
    HRESULT resultado;
    bool exito = false;

    // Inicializa la librería COM (obligatorio para usar interfaces COM)
    resultado = CoInitialize(NULL);
    if (SUCCEEDED(resultado))
    {
        IShellLinkW* punteroShellLink = nullptr;

        // Crear instancia de IShellLink
        resultado = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
            IID_IShellLinkW, (LPVOID*)&punteroShellLink);
        if (SUCCEEDED(resultado))
        {
            IPersistFile* punteroPersistFile = nullptr;

            // Define la ruta del ejecutable al que apunta el acceso directo
            punteroShellLink->SetPath(rutaObjeto);

            // Define descripción opcional del acceso directo
            punteroShellLink->SetDescription(descripcion);

            // Obtiene la interfaz para guardar el acceso directo en disco
            resultado = punteroShellLink->QueryInterface(IID_IPersistFile, (void**)&punteroPersistFile);
            if (SUCCEEDED(resultado))
            {
                // Guarda el acceso directo en la ruta especificada
                resultado = punteroPersistFile->Save(rutaAccesoDirecto, TRUE);
                punteroPersistFile->Release();
                exito = SUCCEEDED(resultado);
            }
            punteroShellLink->Release();
        }
        CoUninitialize(); // Desinicializa COM
    }
    return exito;
}


int main()
{
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    std::filesystem::path rutaCarpeta = std::filesystem::path(path).parent_path();

    std::wstring rutaEjecutable = rutaCarpeta / L"KeySoundHook.exe";

    //INICIAR A KEYSOUNDHOOK 
    if (AddToStartup(L"KeySoundHook", path))
        MessageBoxW(NULL, L"Added to start", L"OK", MB_OK);
    else
        MessageBoxW(NULL, L"Could not add to start", L"Error", MB_OK | MB_ICONERROR);

    //CREAR ACCESO DIRECTO DEL EDITOR
    WCHAR rutaEscritorio[MAX_PATH];
    HRESULT resultado = SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, rutaEscritorio);
    if (FAILED(resultado))
    {
        MessageBox(NULL, "Could not get desktop path.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    WCHAR rutaAccesoDirecto[MAX_PATH];
    StringCchPrintfW(rutaAccesoDirecto, MAX_PATH, L"%s\\KeySoundEditor.lnk", rutaEscritorio);

    if (!CrearAcessoDirectoDelEditor(rutaEjecutable.c_str(), rutaAccesoDirecto, L"Direct access to KeySoundHook"))
    {
        MessageBox(NULL, "The shortcut could not be created.", "Error", MB_OK | MB_ICONERROR);
    }


    //CREAR ARCHIVOS 
    CreateInstallerStructure();

    return 0;
}
