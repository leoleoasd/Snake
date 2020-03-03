#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <iostream>
using namespace std;

int d(int pixels, int mode = 0,int DPI = 0) {
	static double rate = 0;
	if (mode == 0) {
		return pixels * rate;
	}
	else {
		rate = DPI / 96.0;
	}
}

void init() {
	HDC hdc = GetDC(nullptr);
	d(0, 1, GetDeviceCaps(hdc, LOGPIXELSX));
	ReleaseDC(nullptr, hdc);
}

int main()
{
	init();

	initgraph(d(640), d(480));
	fillrectangle(d(200),d(200),d(210),d(300));
	_getch();
	closegraph();
	return 0;
}