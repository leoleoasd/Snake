#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <iostream>
#include <cstring>
using namespace std;
#define WIDTH 220
#define HEIGHT 260

// Colors
// C for normal colors, CT for text colors.
#define C_BACK 0x0
#define C_WALL 0xffffff
#define C_MOUSEDOWN 0xffffff
#define CT_SNAKE 0x0285EE
#define CT_START 0xffffff
#define CT_SCORE 0xffffff

struct funcPtr {
	funcPtr (*next)(void);
	funcPtr operator()(){
		return next();
	}
	funcPtr(funcPtr(*a)(void)) {
		next = a;
	}
};

void setFont(int size) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = size;
	f.lfWidth = size / 2;
	f.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;

	wcscpy_s(f.lfFaceName, L"November");
	settextstyle(&f);
}

void init() {
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	setbkcolor(C_BACK);
	cleardevice();
}

funcPtr start();
funcPtr game();
funcPtr pause();
funcPtr end();

funcPtr start() {
	cleardevice();
	setlinecolor(C_WALL);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE,(10));
	line((5), (5), (5), (215));
	line((5), (5), (215), (5));
	line((215), (5), (215), (215));
	line((5), (215), (215), (215));

	setFont(30);
	settextcolor(CT_SNAKE);
	outtextxy((25), (40), L"Play Snake!");

	setFont(30);
	settextcolor(CT_START);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, (2));
	rectangle((72 - 2), (140 - 2), (148 + 2), (170 + 2));
	outtextxy((72), (140), L"START");
	
	setFont(20);
	settextcolor(CT_SCORE);
	outtextxy((10), (225), L"Scores: 0");
	while (true) {
		auto msg = GetMouseMsg();
		if (70 <= msg.x and msg.x <= 148 and 150 <= msg.y and msg.y <= 172) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				setlinecolor(C_MOUSEDOWN);
				rectangle((72 - 2), (140 - 2), (148 + 2), (170 + 2));
				cout << "Mouse DOWN!";
			}else if (msg.uMsg == WM_LBUTTONUP) {
				// Enter main game function.
				return game;
			}
		}
	}
}

funcPtr game() {
	for (int i = 0; i < HEIGHT; i+=20) {
		clearrectangle(0,i,WIDTH,i+20);
		cout << "Clearing" << 0 << i << WIDTH << i + 20 << endl;
		Sleep(30);
	}
	fillrectangle((20), (20), (100), (90));
	return pause;
}

funcPtr pause() {
	cleardevice();
	fillrectangle((20), (20), (100), (40));
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