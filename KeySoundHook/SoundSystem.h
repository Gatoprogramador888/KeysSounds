#pragma once
#include"Header.h"
#include<filesystem>
#include<experimental/generator>
#include<vector>

namespace fs = std::filesystem;

class Sound {
private:
    Sound() = default;

    LPSTR wstring_to_lpstr(const std::wstring& wstr) {
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
        LPSTR strTo = (LPSTR)malloc(size_needed + 1);
        if (strTo) {
            WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), strTo, size_needed, NULL, NULL);
            strTo[size_needed] = '\0';
        }
        return strTo;
    }



public:
    static Sound& Instance() {
        static Sound instance;
        return instance;
    }

    void Play(const std::wstring& file) {
        PlaySound(wstring_to_lpstr(file), NULL, SND_FILENAME | SND_ASYNC);
    }

    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
};
