#include "Snake.h"
#include <random>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

void init() {
    initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
    setbkcolor(C_BACK);
    cleardevice();
    std::random_device rd;
    srand(rd());

    mciSendString(L"open bgm.mp3 alias bgm", NULL, 0, NULL);
    mciSendString(L"open game.mp3 alias game", NULL, 0, NULL);
}

funcPtr end() {
    // TODO: 展示排行榜
    return nullptr;
}

int main() {
    init();

    funcPtr func = start;
    while (func != nullptr) {
        func = func();
    }

    closegraph();
    return 0;
}