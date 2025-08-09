#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"

class MODMusic : public IMusic
{
private:
    MODMusic() = default;

    static std::string OpenFileDialog(HWND owner)
    {
        OPENFILENAMEA ofn = {};
        CHAR szFile[260] = {};
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = owner;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "Archivos de Música\0*.wav\0Todos los archivos\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = nullptr;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = nullptr;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn)) {
            return std::string(ofn.lpstrFile);
        }
        return ""; // vacío si cancelado
    }

public:
    static MODMusic& Instance()
    {
        static MODMusic instance;
        return instance;
    }

    void Modify()
    {
        HWND listBox = GetItem(LB_LMUSIC);
        int index = SendMessage(listBox, LB_GETCURSEL, NULL, NULL);
        int indexData = SendMessage(listBox, LB_GETITEMDATA, (WPARAM)index, NULL);
        try
        {
            DIR directory = listMusic.at(indexData);
            std::string msgModify = "Do you want to modify " + directory.dir + "?";
            int decision = MessageBox(NULL, msgModify.c_str(), "Modify", MB_YESNO | MB_ICONWARNING);

            if (decision == IDNO)return;

            std::string file = OpenFileDialog(Dlg);
            if (file.empty()) {
                std::cout << "Diálogo cancelado o error." << std::endl;
                return;
            }

            SendMessage(listBox, LB_DELETESTRING, (WPARAM)indexData, NULL);
            directory.dir = file;

            listMusic.at(indexData) = directory;

            SendMessageA(listBox, LB_ADDSTRING, NULL, (LPARAM)file.c_str());
            SendMessageA(listBox, LB_SETITEMDATA, (WPARAM)indexData, (LPARAM)indexData);

            std::string msg = "Modifies " + file;
            MessageBox(NULL, msg.c_str(), "", MB_OK | MB_ICONINFORMATION);

        }
        catch (const std::out_of_range& error)
        {
            std::cerr << error.what() << std::endl;
        }

    }


	MODMusic(const MODMusic&) = delete;
	MODMusic& operator=(const MODMusic&) = delete;
};

