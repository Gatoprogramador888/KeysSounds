#pragma once
#include <Windows.h>
#include <string>

struct DIR_EXPORT {
    std::wstring dir;
    int index;
};

public ref struct DIR_IMPORT
{
    DIR_IMPORT(){}

    DIR_IMPORT(System::String^ _dir, int _index)
    {
        dir = _dir;
        index = _index;
    }

    System::String^ dir = gcnew System::String("");
    int index; 
};

// Punteros a funciones de la DLL
typedef int(__stdcall* fnGetListMusicCount)();
typedef void(__stdcall* fnGetListMusic)(DIR_EXPORT*, int);
typedef void(__stdcall* fnSetListMusic)(DIR_EXPORT*, int);
typedef void(__stdcall* fnAddMusicItem)(std::wstring, int);
typedef void(__stdcall* fnDeleteMusicItem)(int);
typedef void(__stdcall* fnModMusicItem)(int, DIR_EXPORT*);
typedef DIR_EXPORT*(__stdcall* fnGetMusicItem)(int);

public ref class WrapperDIR
{
private:
    HMODULE hDll;
    fnGetListMusicCount pGetCount;
    fnGetListMusic pGetList;
    fnSetListMusic pSetList;
    fnAddMusicItem pAdd;
    fnModMusicItem pUpd;
    fnDeleteMusicItem pDel;
    fnGetMusicItem pGet;

public:
    WrapperDIR(System::String^ dllPath);

    ~WrapperDIR() {
        if (hDll) {
            FreeLibrary(hDll);
            hDll = nullptr;
        }
    }

    // Devuelve lista como Tuple<String^, int>
    //System::Collections::Generic::List<System::Tuple<System::String^, int>^>^ GetMusicList();

    System::Collections::Generic::List<DIR_IMPORT^>^ GetMusicList();

    void SetMusicList(System::Windows::Forms::ListBox::ObjectCollection^ objetos);

    void AddMusic(System::String^ dir, int index);
    
    void DelMusic(int index);

    void UpdMusic(int index, DIR_EXPORT* dir);

    DIR_IMPORT^ GetMusic(int index);

    bool isEmpty();

    size_t Count();
    
};


