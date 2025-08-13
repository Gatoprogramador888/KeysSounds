#pragma once
#include <Windows.h>

// Definiciones de punteros a función
typedef void (*FN_StartAsyncLoad)();
typedef void (*FN_UpdateAsyncLoad)();
typedef bool (*FN_IsLoadDone)();

public ref class LoadMusicWrapper
{
private:
    HMODULE hMusicLib;
    FN_StartAsyncLoad pStartAsyncLoad;
    FN_UpdateAsyncLoad pUpdateAsyncLoad;
    FN_IsLoadDone pIsLoadDone;

public:
    LoadMusicWrapper(System::String^ dllPath);

    ~LoadMusicWrapper(); // Destructor

    void StartAsyncLoad(); 

    bool IsLoadDone(); 

    void UpdateAsyncLoad();

};

