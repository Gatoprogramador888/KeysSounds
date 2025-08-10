#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <string>
#include <string_view>
#include <Windows.h>
#include <vector>

struct DIR
{
    std::wstring dir;
    size_t index = 1;
    bool operator==(const DIR& other) const
    {
        return dir == other.dir && index == other.index;
    }

    DIR& operator=(const DIR& other)
    {
        if (this != &other)
        {
            dir = other.dir;
            index = other.index;
        }
        return *this;
    }
};

extern std::vector<DIR> listMusic;

static std::wstring SStringToWString(const std::string& str)
{
    if (str.empty()) return std::wstring();

    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0],
        (int)str.size(),
        NULL, 0);

    std::wstring wstrTo(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0],
        (int)str.size(),
        &wstrTo[0], sizeNeeded);

    return wstrTo;
}

extern std::wstring StringToWString(const std::string& str);

static std::string SWStringToString(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0],
        (int)wstr.size(),
        NULL, 0, NULL, NULL);

    std::string strTo(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0],
        (int)wstr.size(),
        &strTo[0], sizeNeeded,
        NULL, NULL);

    return strTo;
}

extern std::string WStringToString(const std::wstring& wstr);
