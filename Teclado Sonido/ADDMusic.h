#pragma once
#include"Header.h"
#include<Windows.h>
#include<vector>
#include"resource1.h"


class ADDMusic {
private:
    std::vector<DIR> listMusic;
    size_t index = 0;
    HWND Dlg = nullptr;

    ADDMusic() = default; // Constructor privado para singleton

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
    static ADDMusic& Instance()
    {
        static ADDMusic instance;
        return instance;
    }

    void SetDialogHandle(HWND hwnd)
    {
        Dlg = hwnd;
    }

    void Add()
    {
        std::string file = OpenFileDialog(Dlg);
        if (file.empty()) {
            std::cout << "Diálogo cancelado o error." << std::endl;
            return;
        }

        HWND listBox = GetDlgItem(Dlg, LB_LMUSIC); // Asegúrate que CB_LIST esté definido en resource.h
        SendMessageA(listBox, LB_ADDSTRING, NULL, (LPARAM)file.c_str());
        SendMessageA(listBox, LB_SETCURSEL, (WPARAM)index, NULL);
        //MessageBox(NULL, file.c_str(), "", MB_OK);

        listMusic.push_back(DIR{ file, index });
        ++index;
    }

    const std::vector<DIR>& GetDIRList() const
    {
        return listMusic;
    }

    // Evitar copia
    ADDMusic(const ADDMusic&) = delete;
    ADDMusic& operator=(const ADDMusic&) = delete;
};


