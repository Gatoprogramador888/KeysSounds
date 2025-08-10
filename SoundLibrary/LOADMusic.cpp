#include "pch.h"
#include "LOADMusic.h"
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
    fs::path currentPath = fs::current_path();
    std::string dirFile = currentPath.string() + "\\Music_Directory.txt";
    std::wifstream fileLoad(dirFile);
    size_t index = listMusic.size();

    if (!fileLoad.is_open())
    {
        co_return;
    }

    std::wstring line;

    HWND listBox = GetDlgItem(Dlg, LB_LMUSIC);

    while (std::getline(fileLoad, line))
    {
        SendMessageW(listBox, LB_ADDSTRING, 0, (LPARAM)line.c_str());
        SendMessageA(listBox, LB_SETITEMDATA, (WPARAM)index, (LPARAM)index);

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
        KillTimer(Dlg, 1);
        return;
    }

    ++genLoadFileIt;
}

bool LOADMusic::IsLoadDone() const
{
    return !loading;
}
