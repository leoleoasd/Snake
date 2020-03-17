#include "Snake.h"
using namespace std;

void init() {
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	setbkcolor(C_BACK);
	cleardevice();
}

void draw(snake s) {
	// draw a snake body;

	// 0: 转弯
	// 1: 直, 交叉
	// 2: 直, 直
	// 3: 头
	// 4: 尾
	//
	// 默认方向从右往左。
	int bitmap[][10][10] = {
		#include "body.dat"
	};
	if (s.type == 0)
	{
		if (s.type == snake::TURN)
		{
			// 转弯
			

		}
	}
}


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
		cout << "Get Msg!" << msg.x<<endl;
		if (70 <= msg.x and msg.x <= 150 and 138 <= msg.y and msg.y <= 172) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				setlinecolor(C_MOUSEDOWN);
				rectangle((72 - 2), (140 - 2), (148 + 2), (170 + 2));
				cout << "Mouse DOWN!" << endl;
			}else if (msg.uMsg == WM_LBUTTONUP) {
				// Enter main game function.
				return game;
			}
		}else {
			if (msg.uMsg == WM_LBUTTONUP) {
				setlinecolor(CT_START);
				setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
				rectangle((72 - 2), (140 - 2), (148 + 2), (170 + 2));
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
	fillrectangle(20, 20, 100, 90);
	return pause;
}

funcPtr pause() {
	cleardevice();
	fillrectangle(20, 20,100, 40);
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