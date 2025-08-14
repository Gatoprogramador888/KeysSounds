#include "pch.h"
#include "DinamycListMusic.h"

size_t GetListMusicCount()
{
    return listMusic.size();
}

void SetListMusic(DIR* list, size_t count)
{
    listMusic.clear();
    //size_t limit = (count < listMusic.size()) ? count : listMusic.size();
    for (size_t i = 0; i < count; i++) {
        DIR directory = { list[i].dir, list[i].index };
        listMusic.push_back(directory);
    }
}

void GetListMusic(DIR* buffer, size_t bufferSize)
{
    size_t limit = (bufferSize < listMusic.size()) ? bufferSize : listMusic.size();
    for (int i = 0; i < limit; i++) {
        buffer[i].dir = listMusic[i].dir.c_str();
        buffer[i].index = listMusic[i].index;
    }
}

void AddItem(std::wstring dir, size_t index)
{
    std::wstring sdir = dir;
    DIR directory = { dir, index };
    listMusic.push_back(directory);
}

void DeleteItem(size_t index)
{
    DIR deldir;
    try
    {
        deldir = listMusic.at(index);
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what();
        deldir = listMusic.at(0);
    }
    auto eradir = std::find(listMusic.begin(), listMusic.end(), deldir);
    listMusic.erase(eradir);
}

void UpdateItem(size_t imod, const DIR* dir)
{
    try
    {
        listMusic.at(imod).dir = dir->dir;
        listMusic.at(imod).index = dir->index;
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what();
    }
}

DIR* GetItem(size_t index)
{
    DIR* dir = new DIR({L"", 0});
    try
    {
        DIR gdir = listMusic.at(index);
        dir->dir = gdir.dir;
        dir->index = gdir.index;
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what();
    }
    return dir;
}



