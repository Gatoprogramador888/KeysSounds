#include "Header.h"
#include "SoundSystem.h"
#include <windows.h>
#include <mmsystem.h>
#include "LOADMusic.h"
#include <unordered_set>

// Hook global
HHOOK hHook = NULL;
std::unordered_set<DWORD> keysPressed;
constexpr auto VK_K = 0x4B;
constexpr auto VK_E = 0x45;

// Callback del hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN)
        {
            Sound::Instance().Play(Sound::Instance().RandomSound());
        }

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            keysPressed.insert(pKey->vkCode);

            if ((keysPressed.count(VK_LCONTROL) || keysPressed.count(VK_RCONTROL)) && keysPressed.count(VK_K)) {
                system("KeySoundEditor.exe");
            }

            if ((keysPressed.count(VK_LCONTROL) || keysPressed.count(VK_RCONTROL)) && keysPressed.count(VK_E)) {
                PostQuitMessage(0);
            }
        }
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) 
        {
            keysPressed.erase(pKey->vkCode);
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}


//Timer
HANDLE hTimer = nullptr;

constexpr int DURATION = 50;

VOID CALLBACK TimerQueueRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    LOADMusic::Instance().UpdateAsyncLoad();

    if (LOADMusic::Instance().IsLoadDone())
    {
        DeleteTimerQueueTimer(NULL, hTimer, NULL);
        hTimer = nullptr;
        if (listMusic.empty())
        {
            MessageBox(NULL, "Enter some sounds first", "", MB_OK | MB_ICONINFORMATION);
            system("KeySoundEditor.exe");
        }
        // Notifica fin de carga o setea flag
    }
}

void StartAsyncLoadTimer()
{
    LOADMusic::Instance().StartAsyncLoad();
    CreateTimerQueueTimer(&hTimer, NULL, TimerQueueRoutine, nullptr, NULL, DURATION, NULL);
}

// Punto de entrada WinAPI
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, LPSTR lpstr, int cshow) {
    MSG msg;
    StartAsyncLoadTimer();
    // Instalar hook
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (!hHook) {
        MessageBoxW(NULL, L"No se pudo instalar el hook", L"Error", MB_ICONERROR);
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
