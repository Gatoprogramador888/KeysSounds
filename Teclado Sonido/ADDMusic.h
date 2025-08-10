#pragma once
#include"Header.h"
#include<Windows.h>
#include"resource1.h"
#include "IMusic.h"
#include <locale> // For std::wstring_convert and std::codecvt_utf8
#include <codecvt> // For std::codecvt_utf8


class ADDMusic : public IMusic
{
private:
    //std::vector<DIR> listMusic;
    size_t index = 0;

    ADDMusic() = default; // Constructor privado para singleton

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
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn)) {
            std::string file(ofn.lpstrFile);
            std::wstring wfile = SStringToWString(file);
            return wfile;
        }
        return std::wstring(); // vacío si cancelado
    }

public:
    static ADDMusic& Instance()
    {
        static ADDMusic instance;
        return instance;
    }

    void Add()
    {
        std::wstring wfile = OpenFileDialog(Dlg);
        if (wfile.empty()) {
            std::cout << "Diálogo cancelado o error." << std::endl;
            return;
        }

        index = listMusic.size();
        listMusic.push_back(DIR{ wfile, index });
        std::string file = SWStringToString(wfile);

        HWND listBox = GetItem(LB_LMUSIC);//GetDlgItem(Dlg, LB_LMUSIC);
        SendMessageA(listBox, LB_ADDSTRING, NULL, (LPARAM)file.c_str());
        SendMessageA(listBox, LB_SETITEMDATA, (WPARAM)index, (LPARAM) index);

        std::string msg = "Added " + SWStringToString(wfile) + " with index:" + std::to_string(index);
        MessageBox(NULL, msg.c_str(), "", MB_OK | MB_ICONINFORMATION);
    }

    // Evitar copia
    ADDMusic(const ADDMusic&) = delete;
    ADDMusic& operator=(const ADDMusic&) = delete;
};


