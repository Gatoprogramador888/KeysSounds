#include "LoadMusicWrapper.h"
#include "Editor.h"

LoadMusicWrapper::LoadMusicWrapper(System::String^ dllPath) : hMusicLib(nullptr),
pStartAsyncLoad(nullptr),
pUpdateAsyncLoad(nullptr),
pIsLoadDone(nullptr)
{
    std::wstring wpath = KeySoundEditor::Editor::SysStringToWString(dllPath);
    
    // Cargar la DLL
    hMusicLib = LoadLibrary(wpath.c_str());
    if (!hMusicLib) {
        throw gcnew System::Exception("No se pudo cargar SoundLibrary.dll");
    }

    // Obtener punteros a las funciones
    pStartAsyncLoad = (FN_StartAsyncLoad)GetProcAddress(hMusicLib, "LOADMusic_StartAsyncLoad");
    pUpdateAsyncLoad = (FN_UpdateAsyncLoad)GetProcAddress(hMusicLib, "LOADMusic_UpdateAsyncLoad");
    pIsLoadDone = (FN_IsLoadDone)GetProcAddress(hMusicLib, "LOADMusic_IsLoadDone");

    if (!pStartAsyncLoad || !pUpdateAsyncLoad || !pIsLoadDone) {
        FreeLibrary(hMusicLib);
        hMusicLib = nullptr;
        throw gcnew System::Exception("No se pudieron obtener las funciones de LOADMusic en la DLL");
    }
}

LoadMusicWrapper::~LoadMusicWrapper()
{
    if (hMusicLib) {
        FreeLibrary(hMusicLib);
        hMusicLib = nullptr;
    }
}

void LoadMusicWrapper::StartAsyncLoad()
{
    if (pStartAsyncLoad) pStartAsyncLoad();
}

bool LoadMusicWrapper::IsLoadDone()
{
    return pIsLoadDone ? pIsLoadDone() : false;
}

void LoadMusicWrapper::UpdateAsyncLoad()
{
    if (pUpdateAsyncLoad) pUpdateAsyncLoad();
}

