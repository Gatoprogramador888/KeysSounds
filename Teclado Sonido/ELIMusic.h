#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"
#include "SAVEMusic.h"
#include <algorithm>

class ELIMusic : public IMusic
{
private:
    ELIMusic() = default;

public:
    static ELIMusic& Instance()
    {
        static ELIMusic instance;
        return instance;
    }

    void Eliminate()
    {
        HWND listBox = GetDlgItem(Dlg, LB_LMUSIC);
        LRESULT index = SendMessage(listBox, LB_GETCURSEL, NULL, NULL);
        LRESULT indexData = SendMessage(listBox, LB_GETITEMDATA, (WPARAM)index, NULL);
        DIR directory;
        try
        {
            directory = listMusic.at((int)indexData);
        }
        catch (const std::out_of_range& error)
        {
            std::cerr << error.what() << std::endl;
        }
        std::string msgDelete = "Do you want to delete " + SWStringToString(directory.dir) + "?";
        int decision = MessageBox(NULL, msgDelete.c_str(), "Delete ", MB_YESNO | MB_ICONWARNING);

        if (decision == IDNO)return;

        SendMessage(listBox, LB_DELETESTRING, (WPARAM)indexData, NULL);
        auto objectEliminate = std::find(listMusic.begin(), listMusic.end(), directory);
        if (objectEliminate != listMusic.end()) {
            listMusic.erase(objectEliminate);
        }
        SAVEMusic::Instance().SetSaved();
        std::string msgIndex = SWStringToString(directory.dir) + " was deleted";
        MessageBox(NULL, msgIndex.c_str(), "", MB_OK | MB_ICONINFORMATION);
    }

    // Evitar copia
    ELIMusic(const ELIMusic&) = delete;
    ELIMusic& operator=(const ELIMusic&) = delete;
};

