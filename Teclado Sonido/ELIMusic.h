#pragma once
#include "Header.h"
#include "resource1.h"
#include "SAVEMusic.h"
#include <algorithm>

class ELIMusic
{
private:
    ELIMusic() = default;

public:
    static ELIMusic& Instance()
    {
        static ELIMusic instance;
        return instance;
    }

    void Eliminate(int index);

    // Evitar copia
    ELIMusic(const ELIMusic&) = delete;
    ELIMusic& operator=(const ELIMusic&) = delete;
};

