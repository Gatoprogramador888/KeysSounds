#include "Precompile.h"
#include "resource.h"
#include <Windows.h>

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow)
{
    HWND hMain = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

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