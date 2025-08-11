#pragma once
#include "Header.h"
#include <experimental/generator>

#ifdef MUSICLIBRARY_EXPORTS
#define MUSIC_API __declspec(dllexport)
#else
#define MUSIC_API __declspec(dllimport)
#endif

class MUSIC_API SAVEMusic
{
private:

    std::experimental::generator<std::wstring> saveFile;
    std::experimental::generator<std::wstring>::iterator genSaveFileIt;
    bool saving = false;

    std::experimental::generator<std::wstring> SavesFile();

public:
    static inline SAVEMusic& Instance()
    {
        static SAVEMusic instance;
        return instance;
    }

    void StartAsyncSave();
    void UpdateAsyncSave();
    bool IsSaveDone() const;

    SAVEMusic(const SAVEMusic&) = delete;
    SAVEMusic& operator=(const SAVEMusic&) = delete;

private:
    SAVEMusic() = default;
};
