#include "SavedWrapper.h"
#include "Editor.h"
#include "WrapperDIR.h"
#include <string>

SavedWrapper::SavedWrapper(System::String^ dllPath)
{
    std::wstring wpath = KeySoundEditor::Editor::SysStringToWString(dllPath);

    // Cargar la DLL
    hMusicLib = LoadLibrary(wpath.c_str());
    if (!hMusicLib) {
        throw gcnew System::Exception("No se pudo cargar SoundLibrary.dll");
    }

    // Obtener punteros a las funciones
    pStartAsyncSaved = (FN_StartAsyncLoad)GetProcAddress(hMusicLib, "SAVEMusic_StartAsyncSave");
    pUpdateAsyncSaved = (FN_UpdateAsyncLoad)GetProcAddress(hMusicLib, "SAVEMusic_UpdateAsyncSave");
    pIsSavedDone = (FN_IsLoadDone)GetProcAddress(hMusicLib, "SAVEMusic_IsSaveDone");

    if (!pStartAsyncSaved || !pUpdateAsyncSaved || !pIsSavedDone) {
        FreeLibrary(hMusicLib);
        hMusicLib = nullptr;
        throw gcnew System::Exception("No se pudieron obtener las funciones de LOADMusic en la DLL");
    }
}

SavedWrapper::~SavedWrapper()
{
    if (hMusicLib) {
        FreeLibrary(hMusicLib);
        hMusicLib = nullptr;
    }
}

void SavedWrapper::StartAsyncSaved()
{
    if(pStartAsyncSaved)    
        pStartAsyncSaved();
}

bool SavedWrapper::IsSavedDone()
{
    return pIsSavedDone ? pIsSavedDone() : false;
}

void SavedWrapper::UpdateAsyncSaved()
{
    pUpdateAsyncSaved();
}
