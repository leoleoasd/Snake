#include "Snake.h"

funcPtr start() {
	cleardevice();
	setlinecolor(C_WALL);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
	line(10, 10, 10, 430);
	line(10, 10, 430, 10);
	line(430, 10, 430, 430);
	line(10, 430, 430, 430);

	setFont(60);
	settextcolor(CT_SNAKE);
	outtextxy(50, 80, L"Play Snake!");

	setFont(60);
	settextcolor(CT_START);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 4);
	rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
	outtextxy(2 * (72), 2 * (140), L"START");

	setFont(2 * 20);
	settextcolor(CT_SCORE);
	outtextxy(2 * (10), 2 * (225), L"Scores: 0");
	while (true) {
		auto msg = GetMouseMsg();
		if (140 <= msg.x and msg.x <= 300 and 2 * 138 <= msg.y and msg.y <= 2 * 172) {
			if (msg.uMsg == WM_LBUTTONDOWN) {
				setlinecolor(C_MOUSEDOWN);
				rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
			}
			else if (msg.uMsg == WM_LBUTTONUP) {
				// Enter main game function.
				return game;
			}
		}
		else {
			if (msg.uMsg == WM_LBUTTONUP) {
				setlinecolor(CT_START);
				rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
			}
		}
	}
}