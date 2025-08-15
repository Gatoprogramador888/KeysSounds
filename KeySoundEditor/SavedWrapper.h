#pragma once
#include<Windows.h>

typedef void (*FN_StartAsyncSaved)();
typedef void (*FN_UpdateAsyncSaved)();
typedef bool (*FN_IsSavedDone)();


public ref class SavedWrapper
{
private:
    HMODULE hMusicLib;
    FN_StartAsyncSaved pStartAsyncSaved;
    FN_UpdateAsyncSaved pUpdateAsyncSaved;
    FN_IsSavedDone pIsSavedDone;

public:
    SavedWrapper(System::String^ dllPath);

    ~SavedWrapper();

public:
    void StartAsyncSaved();

    bool IsSavedDone();

    void UpdateAsyncSaved();
};

