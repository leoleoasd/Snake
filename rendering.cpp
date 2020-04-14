#include "Snake.h"

using std::cout;
using std::endl;

int colors[][3] = {
#include "theme.dat"
};
int themes_count = 11;
int theme_selected = 0;

map_t maps[] = {
#include "maps.dat"
};
int maps_count = 3;
int map_selected = 0;


void draw_wall(int x, int y) {
    setlinestyle(PS_NULL);
    setfillcolor(C_WALL);
    setlinecolor(C_WALL);
    fillrectangle(x * SNAKE_SIZE + S_OFFSET_X, y * SNAKE_SIZE + S_OFFSET_Y,
                  (x + 1) * SNAKE_SIZE + S_OFFSET_X,
                  (y + 1) * SNAKE_SIZE + S_OFFSET_Y);
}

void draw_food(int x, int y, int dot) {
    static int data[2][10][10] = {
#include "fruit.dat"
    };
    for (int i = 0; i < SNAKE_SIZE; ++i) {
        for (int j = 0; j < SNAKE_SIZE; ++j) {
            if (data[dot][i / 2][j / 2])
                putpixel(x * SNAKE_SIZE + S_OFFSET_X + i,
                         y * SNAKE_SIZE + S_OFFSET_Y + j, C_FOOD);
        }
    }
}

void setFont(int size) {
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = size;
    f.lfWidth = size / 2;
    f.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;

    wcscpy_s(f.lfFaceName, L"November");
    settextstyle(&f);
}

// Side: 右 0 左 1
void _draw_real(SnakeNode& s, bool dot, int last_side) {
    int nowtype = 2 * ((int)s.type) + last_side;

    // DIRECT,DIRECT2,TURN,TURN2, HEAD1,HEAD2, TAIL1,TAIL2

    // std::cout << "x" << s.x << "y" << s.y << "s" << (int)s.type << "l" <<
    // last_side << nowtype<< std::
    ;
    // 绘制蛇的一节
    // 默认方向从右往左。

    static int bitmap[][2][SNAKE_SIZE][SNAKE_SIZE] = {
#include "body.dat"
    };

    int nowx, nowy, temp;
    for (int i = 0; i < SNAKE_SIZE; ++i) {
        for (int j = 0; j < SNAKE_SIZE; ++j) {
            nowx = i;
            nowy = j;
            for (int _ = 0; _ < s.direction; ++_) {
                temp = nowx;
                nowx = SNAKE_SIZE - 1 - nowy;
                nowy = temp;
            }
            // DIRECT_SWITCH, DIRECT_SWITCH2,DIRECT,TURN, HEAD, TAIL
            switch (bitmap[nowtype][dot][nowy][nowx]) {
                case 1:
                    putpixel(s.x * SNAKE_SIZE + S_OFFSET_X + i,
                             s.y * SNAKE_SIZE + S_OFFSET_Y + j, C_SB);
                    break;
                case 2:
                    putpixel(s.x * SNAKE_SIZE + S_OFFSET_X + i,
                             s.y * SNAKE_SIZE + S_OFFSET_Y + j, C_SD);
                    break;
            }
        }
    }
}

void draw(Snake& s, bool dot) {
    draw(&s, dot);
}

void draw(Snake* ss, bool dot) {
    int last = ss->status;
    SnakeNode* s = ss->s;
    while (s != nullptr) {
        _draw_real(*s, dot, last);
        last = 1 - last;
        s = s->next;
    }
}