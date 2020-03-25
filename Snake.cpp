#include "Snake.h"

using namespace std;

void init() {
	
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	setbkcolor(C_BACK);
	cleardevice();
}


funcPtr pause() {
	cleardevice();
	fillrectangle(2 * 20, 2 * 20, 2 * 100, 2 * 40);
	return game;
}

funcPtr end() {
	// TODO: 展示排行榜
	return nullptr;
}

int main()
{
	init();

	funcPtr func = start;
	while (func.next != nullptr) {
		func = func();
	}

	closegraph();
	return 0;
}