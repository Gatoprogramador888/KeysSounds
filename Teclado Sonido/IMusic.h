#pragma once
#include "resource1.h"
#include "Header.h"
#include <vector>

class IMusic
{
protected:
    HWND Dlg = nullptr;

    virtual HWND GetItem(const int& item) final
    {
        return GetDlgItem(Dlg, item);
    }

    virtual std::vector<HWND> GetItems() final
    {
        std::vector<HWND> items;
        items.push_back(GetDlgItem(Dlg, BTN_ADD));
        items.push_back(GetDlgItem(Dlg, BTN_ELI));
        items.push_back(GetDlgItem(Dlg, BTN_MOD));
        items.push_back(GetDlgItem(Dlg, LB_LMUSIC));
        return items;
    }

public:
    virtual void SetDialogHandle(HWND hwnd) final
    {
        Dlg = hwnd;
    }

};

