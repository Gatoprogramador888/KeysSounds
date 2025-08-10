#pragma once
#include "IMusic.h"
#include "Header.h"
#include <experimental/generator>

#ifdef MUSICLIBRARY_EXPORTS
#define MUSIC_API __declspec(dllexport)
#else
#define MUSIC_API __declspec(dllimport)
#endif

class MUSIC_API LOADMusic : public IMusic
{
private:
    LOADMusic() = default;

    std::experimental::generator<std::wstring> loadFile;
    std::experimental::generator<std::wstring>::iterator genLoadFileIt;
    bool loading = false;

    std::experimental::generator<std::wstring> LoadsFile();

    int LB_LMUSIC;

public:
    static LOADMusic& Instance();

    void StartAsyncLoad();
    void UpdateAsyncLoad();
    bool IsLoadDone() const;

    void SetDialogHandle(const int& LB) { LB_LMUSIC = LB; }

    LOADMusic(const LOADMusic&) = delete;
    LOADMusic& operator=(const LOADMusic&) = delete;

};


