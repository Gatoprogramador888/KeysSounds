#pragma once
#include "Header.h"

extern "C" {
    MUSIC_API size_t GetListMusicCount(); 

    MUSIC_API void SetListMusic(DIR* list, size_t count);

    MUSIC_API void GetListMusic(DIR* buffer, size_t bufferSize);  

    MUSIC_API void AddItem(std::wstring dir, size_t index); 

    MUSIC_API void DeleteItem(size_t index); 

    MUSIC_API void UpdateItem(size_t imod, const DIR* dir); 
    
    MUSIC_API DIR* GetItem(size_t index); 

}
