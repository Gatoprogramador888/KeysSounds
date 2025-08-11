#pragma once
#include "Header.h"
#include <experimental/generator>

#ifdef MUSICLIBRARY_EXPORTS
#define MUSIC_API __declspec(dllexport)
#else
#define MUSIC_API __declspec(dllimport)
#endif

class MUSIC_API LOADMusic
{
private:
    LOADMusic() = default;

    std::experimental::generator<std::wstring> loadFile;
    std::experimental::generator<std::wstring>::iterator genLoadFileIt;
    bool loading = false;

    std::experimental::generator<std::wstring> LoadsFile();

public:
    static LOADMusic& Instance();

    void StartAsyncLoad();
    void UpdateAsyncLoad();
    bool IsLoadDone() const;

    LOADMusic(const LOADMusic&) = delete;
    LOADMusic& operator=(const LOADMusic&) = delete;

};


