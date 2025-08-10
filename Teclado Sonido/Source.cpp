#include "Header.h"
#include "resource1.h"
#include "ADDMusic.h"
#include "ELIMusic.h"
#include "MODMusic.h"
#include "SAVEMusic.h"
#include "LOADMusic.h"
#include <Windows.h>

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

constexpr int IDLOAD = 1;
constexpr int IDSAVED = 2;
constexpr int SLEEPTIMER = 50;

void startLoad(HWND hMain)
{
    
    LOADMusic::Instance().SetDialogParent(hMain);
    LOADMusic::Instance().SetLBMusic(LB_LMUSIC);
    LOADMusic::Instance().StartAsyncLoad();
    SetTimer(hMain, IDLOAD, SLEEPTIMER, NULL);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow)
{
    HWND hMain = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

    startLoad(hMain);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    ShowWindow(hMain, SW_SHOW);

    ADDMusic::Instance().SetDialogParent(hMain);
    ELIMusic::Instance().SetDialogParent(hMain);
    MODMusic::Instance().SetDialogParent(hMain);
    SAVEMusic::Instance().SetDialogParent(hMain);
    SAVEMusic::Instance().SetButtonHandle(BTN_SAVE);

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
            ADDMusic::Instance().Add();
        }

        if (LOWORD(wParam) == BTN_ELI)
        {
            ELIMusic::Instance().Eliminate();
        }

        if (LOWORD(wParam) == BTN_MOD)
        {
            MODMusic::Instance().Modify();
        }

        if (LOWORD(wParam) == BTN_SAVE)
        {
            SAVEMusic::Instance().StartAsyncSave();
            SetTimer(hDlg, IDSAVED, SLEEPTIMER, NULL);
            
        }
    }
    break;
    case WM_TIMER:
        if (wParam == IDLOAD)
        {
            LOADMusic::Instance().UpdateAsyncLoad();
            if (LOADMusic::Instance().IsLoadDone())
            {
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