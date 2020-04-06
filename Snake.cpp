#include "Snake.h"
#include <random>
using namespace std;

void init() {
    initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
    setbkcolor(C_BACK);
    cleardevice();
    std::random_device rd;
    srand(rd());
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