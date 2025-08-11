#pragma once
#include "Header.h"
#include "resource1.h"
#include "SAVEMusic.h"
#include<commdlg.h>

class MODMusic
{
private:
    MODMusic() = default;


public:
    static MODMusic& Instance()
    {
        static MODMusic instance;
        return instance;
    }

    DIR Modify(int index);


	MODMusic(const MODMusic&) = delete;
	MODMusic& operator=(const MODMusic&) = delete;
};

