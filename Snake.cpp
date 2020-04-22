#include "Snake.h"

#include <locale>
#include <random>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

std::queue<wchar_t> key_queue;

LRESULT CALLBACK GetMsgProc(_In_ int nCode,
                            _In_ WPARAM wParam,
                            _In_ LPARAM lParam) {
    if (nCode < 0 || wParam == 0)
        return CallNextHookEx(NULL, nCode, wParam,
                              lParam);

    auto msg = (MSG *)lParam;

    static wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>>
    conv1(
      new std::codecvt_byname<wchar_t, char, mbstate_t>(
          ".936"));
    switch (msg->message) {
        case WM_CHAR:
            key_queue.push(msg->wParam);
            if (msg->wParam > 0xd800) {
                cout << "??";
            } else {
                cout << conv1.to_bytes(msg->wParam);
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