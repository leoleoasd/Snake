#include "Snake.h"


void setFont(int size) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = size;
	f.lfWidth = size / 2;
	f.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;

	wcscpy_s(f.lfFaceName, L"November");
	settextstyle(&f);
}



void draw(Snake &s, int dot) {
	// 绘制蛇的一节
	// 默认方向从右往左。
	
	static int bitmap[][2][SNAKE_SIZE][SNAKE_SIZE] = {
		#include "body.dat"
	};
	int nowx, nowy, temp;
	BeginBatchDraw();
	for (int i = 0; i < SNAKE_SIZE; ++i)
	{
		for (int j = 0; j < SNAKE_SIZE; ++j)
		{
			nowx = i;
			nowy = j;
			for (int _ = 0; _ < s.direction; ++_)
			{
				temp = nowx;
				nowx = SNAKE_SIZE - 1 - nowy;
				nowy = temp;
			}
			switch (bitmap[(int)s.type][dot][nowx][nowy])
			{
			case 1:
				putpixel(
					s.x * SNAKE_SIZE + S_OFFSET_X + i,
					s.y * SNAKE_SIZE + S_OFFSET_Y + j,
					C_SB
				);
				break;
			case 2:
				putpixel(
					s.x * SNAKE_SIZE + S_OFFSET_X + i,
					s.y * SNAKE_SIZE + S_OFFSET_Y + j,
					C_SD
				);
				break;
			}
		}
	}
	EndBatchDraw();
}