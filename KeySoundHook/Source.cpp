#include "Header.h"
#include "SoundSystem.h"
#include "Settings.h"
#include <windows.h>
#include <mmsystem.h>
#include "LOADMusic.h"
#include <unordered_set>
#include <chrono>

// Hook global
HHOOK hHook = NULL;
std::unordered_set<DWORD> keysPressed;
constexpr auto VK_K = 0x4B;
constexpr auto VK_E = 0x45;
std::chrono::steady_clock::time_point lastCall = std::chrono::steady_clock::now();

const wchar_t* EVENT_NAME = L"Global\\StopHookEvent";

// Callback del hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN)
        {
            Sound::Instance().Play();
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
        auto now = std::chrono::steady_clock::now();
        if (now - lastCall < std::chrono::milliseconds(500))
            return; // No pasa suficiente tiempo, espera más

        lastCall = now;

        BOOL is_delete = DeleteTimerQueueTimer(NULL, hTimer, NULL);
        if(!is_delete)
        {
            DWORD errorCode = GetLastError();
            if (errorCode == ERROR_IO_PENDING)
            {
                DWORD waitResult = WaitForSingleObject(hTimer, 5000);
                if (waitResult == WAIT_OBJECT_0) 
                {
                    MessageBox(NULL, "I finish the failed upload", "info", MB_OK | MB_ICONEXCLAMATION);
                }
            }
            else
            { 
                // Falló al eliminar el timer
                wchar_t errorMsg[256];
                swprintf(errorMsg, 256, L"Error deleting timer: %lu\n", errorCode);
                MessageBoxW(NULL, errorMsg, L"Error", MB_OK | MB_ICONERROR);
            }
        }

        hTimer = nullptr;
        
        if (listMusic.empty())
        {
            MessageBox(NULL, "Enter some sounds first", "", MB_OK | MB_ICONINFORMATION);
            std::exit(0);
            system("KeySoundEditor.exe");
        }
        // Notifica fin de carga o setea flag
        std::string msg = std::to_string(listMusic.size() - 1) + " sounds were loaded";
    }
}

void StartAsyncLoadTimer()
{
    LOADMusic::Instance().StartAsyncLoad();
    BOOL is_create = CreateTimerQueueTimer(&hTimer, NULL, TimerQueueRoutine, nullptr, NULL, DURATION, NULL);
    if (!is_create)
    {
        // Falló al eliminar el timer
        DWORD errorCode = GetLastError();
        wchar_t errorMsg[256];
        swprintf(errorMsg, 256, L"Error creating timer: %lu\n", errorCode);
        MessageBoxW(NULL, errorMsg, L"Error", MB_OK | MB_ICONERROR);
    }

}

// Punto de entrada WinAPI
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, LPSTR lpstr, int cshow) {
    Settings::Instance().ReadSettings();
    StartAsyncLoadTimer();

    //Crear el evento
    HANDLE hStopEvent = CreateEventW(NULL, TRUE, FALSE, EVENT_NAME);
    if (!hStopEvent)
    {
        MessageBoxW(NULL, L"Could not create StopHookEvent event", L"Error", MB_ICONERROR);
        return -1;
    }

    // Instalar hook
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (!hHook) {
        MessageBoxW(NULL, L"The hook could not be installed", L"Error", MB_ICONERROR);
        return -1;
    }


    MSG msg;
    bool running = true;

    while (running)
    {
        DWORD waitResult = MsgWaitForMultipleObjects(1, &hStopEvent, FALSE, INFINITE, QS_ALLINPUT);

        if (waitResult == WAIT_OBJECT_0)
        {
            // Evento activado: salir del loop
            running = false;
        }
        else if (waitResult == WAIT_OBJECT_0 + 1)
        {
            // Hay mensajes en la cola, procesarlos
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    running = false;
                    break;
                }
                else if(!running)
                {
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    UnhookWindowsHookEx(hHook);
    CloseHandle(hStopEvent);

    MessageBox(NULL, "closing Key Sound", "Info", MB_OK | MB_ICONINFORMATION);

    return 0;
}
