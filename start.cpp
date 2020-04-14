#include "Snake.h"

Snake* makeDemoSnake() {
    Snake* ret = new Snake;
    ret->heading = 0;
    ret->s = new SnakeNode(8, 9, 0, SnakeType::HEAD);
    SnakeNode* tail = ret->s;
    tail->next = new SnakeNode(9, 9, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(10, 9, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(11, 9, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(12, 9, 0, SnakeType::TAIL);
    tail = tail->next;
    return ret;
}

funcPtr start() {
    cleardevice();
    Snake* s = makeDemoSnake();
    int hovering = 0;
    mciSendString(L"play bgm repeat", NULL, 0, NULL);

    while (true) {
        if (MouseHit()) {
            auto msg = GetMouseMsg();
            while (MouseHit()) {
                msg = GetMouseMsg();
            }
            if (140 <= msg.x and msg.x <= 300 and 2 * 138 <= msg.y and
                msg.y <= 2 * 172) {
                hovering = 1;
                if (msg.uMsg == WM_LBUTTONUP) {
                    // Enter main game function.
                    return game;
                }
            } else {
                hovering = 0;
                if (msg.uMsg == WM_LBUTTONUP) {
                    setlinecolor(CT_START);
                    rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2),
                              2 * (170 + 2));
                }
            }
        }
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case KEY_LEFT:
                    theme_selected = (theme_selected + 1) % themes_count;
                    break;
                case KEY_RIGHT:
                    theme_selected =
                        (theme_selected + themes_count - 1) % themes_count;
                    break;
                case KEY_UP:
                    map_selected = (map_selected + maps_count - 1) % maps_count;
                    break;
                case KEY_DOWN:
                    map_selected = (map_selected + 1) % maps_count;
                    break;
                case '\r':
                case ' ':
                    return game;
            }
        }


        BeginBatchDraw();
        cleardevice();
        setlinecolor(C_SB);
        setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
        line(10, 10, 10, 430);
        line(10, 10, 430, 10);
        line(430, 10, 430, 430);
        line(10, 430, 430, 430);

        
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (maps[map_selected][i][j] == 1) {
                    draw_wall(i, j);
                }
            }
        }
        draw_food(7, 9, 0);


        draw(s, 1);

        setFont(60);
        setbkmode(TRANSPARENT);
        settextcolor(CT_SNAKE);
        outtextxy(50, 80, L"Play Snake!");

        setFont(60);
        settextcolor(CT_START);
        setlinecolor(hovering ? C_MOUSEDOWN : CT_START);
        setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 4);
        rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
        outtextxy(2 * (72), 2 * (140), L"START");

        setFont(2 * 20);
        settextcolor(CT_SCORE);
        setlinecolor(CT_SCORE);
        outtextxy(2 * (10), 2 * (225), L"Scores: 0");
        EndBatchDraw();

        Sleep(20);
    }
}