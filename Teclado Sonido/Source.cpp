#include "Header.h"
#include "resource1.h"
#include "ADDMusic.h"
#include "ELIMusic.h"
#include "MODMusic.h"
#include "SAVEMusic.h"
#include "LOADMusic.h"
#include <Windows.h>
#include "UI.h"

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

constexpr int IDLOAD = 1;
constexpr int IDSAVED = 2;
constexpr int SLEEPTIMER = 50;

void startLoad(HWND hMain)
{
    LOADMusic::Instance().StartAsyncLoad();
    SetTimer(hMain, IDLOAD, SLEEPTIMER, NULL);
}

void StartUI(HWND hMain)
{
    HWND hListBox = GetDlgItem(hMain, LB_LMUSIC);
    UIListBox::Instance().SethObject(hListBox);

    HWND hButtonSaved = GetDlgItem(hMain, BTN_SAVE);
    UIButtonSaved::Instance().SethObject(hButtonSaved);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow)
{
    HWND hMain = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    startLoad(hMain);
    StartUI(hMain);
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    ShowWindow(hMain, SW_SHOW);


    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        // Inicialización si se desea
        return TRUE;

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == BTN_ADD)
        {

            DIR add = ADDMusic::Instance().Add();

            if(!add.Empty())
                UIListBox::Instance().SetItem(add);

            UIButtonSaved::Instance().SetButtonNotSaved();
        }

        if (LOWORD(wParam) == BTN_ELI)
        {
            int index = UIListBox::Instance().GetItemSelect();
            ELIMusic::Instance().Eliminate(index);
            UIListBox::Instance().DeleteItem(index);

            UIButtonSaved::Instance().SetButtonNotSaved();
        }

        if (LOWORD(wParam) == BTN_MOD)
        {
            int index = UIListBox::Instance().GetItemSelect();
            UIListBox::Instance().DeleteItem(index);
            DIR mod = MODMusic::Instance().Modify(index);

            if (!mod.Empty())
                UIListBox::Instance().SetItem(mod);

            UIButtonSaved::Instance().SetButtonNotSaved();
        }

        if (LOWORD(wParam) == BTN_SAVE)
        {
            SAVEMusic::Instance().StartAsyncSave();
            SetTimer(hDlg, IDSAVED, SLEEPTIMER, NULL);

            UIButtonSaved::Instance().SetButtonYesSaved();
            
        }
    }
    break;
    case WM_TIMER:
        if (wParam == IDLOAD)
        {
            LOADMusic::Instance().UpdateAsyncLoad();
            if (LOADMusic::Instance().IsLoadDone())
            {
                UIListBox::Instance().Load();
                KillTimer(hDlg, IDLOAD);
            }
        }
        if (wParam == IDSAVED)
        {
            SAVEMusic::Instance().UpdateAsyncSave();
            if (SAVEMusic::Instance().IsSaveDone())
            {
                KillTimer(hDlg, IDSAVED);
                MessageBox(hDlg, "Saving completed", "Saving", MB_OK);
            }
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }

    return FALSE;
}