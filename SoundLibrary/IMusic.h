#pragma once
#include <Windows.h>

#ifdef MUSICLIBRARY_EXPORTS
#define MUSIC_API __declspec(dllexport)
#else
#define MUSIC_API __declspec(dllimport)
#endif

class MUSIC_API IMusic
{
protected:
    HWND Dlg = nullptr;

public:
    virtual void SetDialogHandle(HWND hwnd)
    {
        Dlg = hwnd;
    }

    virtual HWND GetDialogHandle() const
    {
        return Dlg;
    }

    virtual ~IMusic() = default;
};
