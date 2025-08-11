#pragma once
#include"pch.h"

#ifdef MUSICLIBRARY_EXPORTS
#define MUSIC_API __declspec(dllexport)
#else
#define MUSIC_API __declspec(dllimport)
#endif

struct DIR
{
    std::wstring dir;
    size_t index = 0;

    bool Empty()
    {
        return (dir.empty() && index == NULL);
    }

    bool operator==(const DIR& other) const
    {
        return dir == other.dir && index == other.index;
    }

    DIR& operator=(const DIR& other)
    {
        if (this != &other)
        {
            dir = other.dir;
            index = other.index;
        }
        return *this;
    }
};

// Variable global lista de música (dentro de DLL)
extern MUSIC_API std::vector<DIR> listMusic;

// Funciones de conversión exportadas
MUSIC_API std::wstring StringToWString(const std::string& str);
MUSIC_API std::string WStringToString(const std::wstring& wstr);

// Si quieres dejar funciones auxiliares estáticas internas, las puedes dejar sin exportar
static std::wstring SStringToWString(const std::string& str)
{
    if (str.empty()) return std::wstring();
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], sizeNeeded);
    return wstrTo;
}

static std::string SWStringToString(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
    return strTo;
}


//OPENFILENAME

static std::wstring OpenFileDialog()
{
    OPENFILENAME ofn = {};
    CHAR szFile[260] = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
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

static std::wstring OpenFileDialog(HWND hwnd)
{
    OPENFILENAME ofn = {};
    CHAR szFile[260] = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
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