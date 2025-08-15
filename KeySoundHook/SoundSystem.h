#pragma once
#include"Header.h"
#include <mmsystem.h>
#include <random>
#include<Windows.h>


class Sound {
private:
    Sound() = default;

public:
    static Sound& Instance() {
        static Sound instance;
        return instance;
    }


    std::wstring RandomSound();
    

    void Play(const std::wstring& file) {
        PlaySoundW(file.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }

    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
};
