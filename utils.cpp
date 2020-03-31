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

void _draw_real(SnakeType last,Snake& s, bool dot)
{
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
			// DIRECT_SWITCH, DIRECT_SWITCH2,DIRECT,TURN, HEAD, TAIL
			switch (bitmap[(int)s.type][dot][nowy][nowx])
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

void draw(Snake& s, bool dot) {
	_draw_real(SnakeType::DIRECT, s, dot);
}

void draw(Snake* s, bool dot) {
	_draw_real(SnakeType::DIRECT,*s, dot);
}