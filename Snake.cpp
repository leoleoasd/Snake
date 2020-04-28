#include "Snake.h"

#include <locale>
#include <random>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

std::queue<wchar_t> char_queue;
std::queue<int> key_queue;

LRESULT CALLBACK GetMsgProc(_In_ int nCode,
                            _In_ WPARAM wParam,
                            _In_ LPARAM lParam) {
    if (nCode < 0 || wParam == 0)
        return CallNextHookEx(NULL, nCode, wParam,
                              lParam);
    auto msg = (MSG *)lParam;
    switch (msg->message) {
        case WM_CHAR:
            char_queue.push(msg->wParam);
            return 1;
        case WM_KEYDOWN:
            if (msg->wParam != 229) { // Ignore place holder key codes.
                key_queue.push(msg->wParam);
            }
            return 1;
    }
    return CallNextHookEx(
        NULL, nCode, wParam,
        lParam);
}

void init() {
    HWND hWnd = initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
    SetWindowsHookEx(
        WH_GETMESSAGE, GetMsgProc,
        NULL,
        GetWindowThreadProcessId(hWnd, NULL));
    setbkcolor(C_BACK);
    cleardevice();

    mciSendString(L"open bgm.mp3 alias bgm", NULL, 0, NULL);
    mciSendString(L"open game.mp3 alias game", NULL, 0, NULL);
}

funcPtr end() {
    // TODO: 展示排行榜
    return nullptr;
}

int wmain() {
    init();

    funcPtr func = start;
    while (func != nullptr) {
        func = func();
    }

    closegraph();
    return 0;
}