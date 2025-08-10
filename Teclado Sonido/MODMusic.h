#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"
#include "SAVEMusic.h"
#include<commdlg.h>

class MODMusic : public IMusic
{
private:
    MODMusic() = default;

    static std::wstring OpenFileDialog(HWND owner)
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
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn)) {
            std::string file(ofn.lpstrFile);
            std::wstring wfile = SStringToWString(file);
            return wfile;
        }
        return std::wstring(); // vacío si cancelado
    }


public:
    static MODMusic& Instance()
    {
        static MODMusic instance;
        return instance;
    }

    void Modify()
    {
        HWND listBox = GetDlgItem(Dlg, LB_LMUSIC);
        LRESULT index = SendMessage(listBox, LB_GETCURSEL, NULL, NULL);
        LRESULT indexData = SendMessage(listBox, LB_GETITEMDATA, (WPARAM)index, NULL);
        try
        {
            DIR directory = listMusic.at((int)indexData);
            std::string msgModify = "Do you want to modify " + SWStringToString(directory.dir) + "?";
            int decision = MessageBox(NULL, msgModify.c_str(), "Modify", MB_YESNO | MB_ICONWARNING);

            if (decision == IDNO)return;

            std::wstring wfile = OpenFileDialog(Dlg);
            if (wfile.empty()) {
                std::cout << "Diálogo cancelado o error." << std::endl;
                return;
            }

            SendMessage(listBox, LB_DELETESTRING, (WPARAM)indexData, NULL);
            directory.dir = wfile;
            listMusic.at(indexData) = directory;

            //std::string file = SWStringToString(wfile);

            SendMessageW(listBox, LB_ADDSTRING, NULL, (LPARAM)wfile.c_str());
            SendMessageA(listBox, LB_SETITEMDATA, (WPARAM)indexData, (LPARAM)indexData);

            std::string msg = "Modifies " + SWStringToString(wfile);
            MessageBox(NULL, msg.c_str(), "", MB_OK | MB_ICONINFORMATION);
            SAVEMusic::Instance().SetSaved();
        }
        catch (const std::out_of_range& error)
        {
            std::cerr << error.what() << std::endl;
        }

    }


	MODMusic(const MODMusic&) = delete;
	MODMusic& operator=(const MODMusic&) = delete;
};

