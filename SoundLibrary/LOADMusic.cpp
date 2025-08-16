#include "pch.h"
#include "LOADMusic.h"
#include "Settings.h"
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;

LOADMusic& LOADMusic::Instance()
{
    static LOADMusic instance;
    return instance;
}

std::experimental::generator<std::wstring> LOADMusic::LoadsFile()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path currentPath = fs::path(exePath).parent_path();
    std::wstring dirFile = currentPath.wstring() + L"\\" + Settings::Instance().GetConfigurationAddress();
    //MessageBoxW(NULL, dirFile.c_str(), L"info", MB_OK);
    std::wifstream fileLoad(dirFile);
    //size_t index = listMusic.size();
    size_t index = 1;

    if (!fileLoad.is_open())
    {
        MessageBoxW(NULL, (L"Could not read " + dirFile).c_str(), L"Error", MB_OK | MB_ICONERROR);
        co_return;
    }

    std::wstring line;

    while (std::getline(fileLoad, line))
    {

        DIR directory;
        directory.dir = line;
        directory.index = index;
        listMusic.push_back(directory);

        index = listMusic.size();
        co_yield line;
    }

    fileLoad.close();
}

void LOADMusic::StartAsyncLoad()
{
    listMusic.clear();
    loadFile = LoadsFile();
    genLoadFileIt = loadFile.begin();
    loading = true;
}

void LOADMusic::UpdateAsyncLoad()
{
    if (!loading)
        return;

    if (genLoadFileIt == loadFile.end())
    {
        loading = false;
        loadFile = std::experimental::generator<std::wstring>(); // reset generator
        return;
    }

    ++genLoadFileIt;
}

bool LOADMusic::IsLoadDone() const
{
    return !loading;
}

LOADMusic* LOADMusic_Instance()
{
    return &LOADMusic::Instance();
}

void LOADMusic_StartAsyncLoad()
{
    LOADMusic::Instance().StartAsyncLoad();
}

void LOADMusic_UpdateAsyncLoad()
{
    LOADMusic::Instance().UpdateAsyncLoad();
}

bool LOADMusic_IsLoadDone()
{
    return LOADMusic::Instance().IsLoadDone();
}

