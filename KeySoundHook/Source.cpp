#include "Header.h"
#include "SoundSystem.h"

// Hook global
HHOOK hHook = NULL;

// Callback del hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN) {
            // Ejemplo: reproducir un sonido al presionar la tecla "A"
            if (pKey->vkCode == 0x41) { // 0x41 = 'A'
                Sound::Instance().Play(L"C:\\ruta\\sonido.wav");
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

// Punto de entrada WinAPI
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    MSG msg;

    // Instalar hook
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (!hHook) {
        //MessageBox(NULL, L"No se pudo instalar el hook", L"Error", MB_ICONERROR);
        return -1;
    }

    // Bucle de mensajes
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
