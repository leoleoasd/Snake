#include "Snake.h"

#include <locale>
#include <random>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include <imm.h>
#pragma comment(lib, "imm32.lib")
using namespace std;

std::queue<wchar_t> char_queue;
std::queue<int> key_queue;
HWND hWnd;

LRESULT CALLBACK GetMsgProc(_In_ int nCode,
                            _In_ WPARAM wParam,
                            _In_ LPARAM lParam) {
    auto msg = (MSG*)lParam;
    if (msg->message == WM_IME_COMPOSITION) {
        cout << 123 << endl;
    }
    if (nCode < 0 || wParam == 0)
        return CallNextHookEx(NULL, nCode, wParam,
                              lParam);
    switch (msg->message) {
        case WM_CHAR:
            char_queue.push(msg->wParam);
            return 1;
        case WM_KEYDOWN:
            if (msg->wParam != 229) { // Ignore place holder key codes.
                key_queue.push(msg->wParam);
            } else {
                HIMC hIMC = ImmGetContext(hWnd);  //获取
                if (hIMC) {
                    COMPOSITIONFORM Composition;
                    Composition.dwStyle = CFS_POINT;
                    Composition.ptCurrentPos.x = cur_x;
                    Composition.ptCurrentPos.y = cur_y;
                    ImmSetCompositionWindow(hIMC, &Composition);  //设置

                    ImmReleaseContext(hWnd, hIMC);  //释放
                }  
            }
            return 1;
    }
    return CallNextHookEx(
        NULL, nCode, wParam,
        lParam);
}

void init() {
    hWnd = initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
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