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

void CreateFileMusic()
{
    try {
        fs::path pathOrigin = fs::current_path();

        // Carpetas
        fs::path pathMusicFolder = pathOrigin / "Music";     // Donde irá Music_Directory.txt
        fs::path pathMusics = pathOrigin / "Musics";         // Carpeta con sonidos
        fs::path pathSettings = pathOrigin / "Settings";     // Carpeta con Settings.txt y MainConfiguration.txt

        // Crear carpetas si no existen
        fs::create_directories(pathMusicFolder);
        fs::create_directories(pathSettings);

        // Rutas de los archivos
        fs::path fileMusicDirectory = pathMusicFolder / "Music_Directory.txt";
        fs::path fileSettings = pathSettings / "Settings.txt";
        fs::path fileMainConfig = pathSettings / "MainConfiguration.txt";

        // Validar Musics
        if (!fs::exists(pathMusics) || !fs::is_directory(pathMusics)) {
            MessageBoxW(NULL, L"The 'Musics' directory does not exist or is invalid", L"Error", MB_OK | MB_ICONERROR);
            return;
        }

        // Escribir Music_Directory.txt con lista de canciones
        {
            std::wofstream file(fileMusicDirectory);
            if (!file) {
                MessageBoxW(NULL, L"Cannot create Music_Directory.txt", L"Error", MB_OK | MB_ICONERROR);
                return;
            }

            for (const auto& entry : fs::directory_iterator(pathMusics)) {
                if (fs::is_regular_file(entry.path())) {
                    file << entry.path().filename().wstring() << L"\n";
                }
            }
        }

        // Escribir "Music_Directory" en Settings.txt y MainConfiguration.txt
        {
            std::wofstream settingsFile(fileSettings);
            settingsFile << L"Music_Directory\n";
        }
        {
            std::wofstream mainConfigFile(fileMainConfig);
            mainConfigFile << L"Music_Directory\n";
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
    CreateFileMusic();

    return 0;
}
