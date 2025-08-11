#pragma once
#include"Header.h"
#include<commdlg.h>
#include"resource1.h"
#include "SAVEMusic.h"


class ADDMusic
{
private:
    //std::vector<DIR> listMusic;
    size_t index = 0;

    ADDMusic() = default; // Constructor privado para singleton

public:
    static ADDMusic& Instance()
    {
        static ADDMusic instance;
        return instance;
    }

    DIR Add();

    // Evitar copia
    ADDMusic(const ADDMusic&) = delete;
    ADDMusic& operator=(const ADDMusic&) = delete;
};


