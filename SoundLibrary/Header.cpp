#include "pch.h"
#include "Header.h"

MUSIC_API std::vector<DIR> listMusic;

extern "C" MUSIC_API const wchar_t* StringToWString(const std::string & str)
{
    if (str.empty()) return L"";

    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], sizeNeeded);
    static std::wstring returns = wstrTo;
    return returns.c_str();
}

extern "C" MUSIC_API const char* WStringToString(const std::wstring & wstr)
{
    if (wstr.empty()) return "";

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
    static std::string returns = strTo;
    return returns.c_str();
}
