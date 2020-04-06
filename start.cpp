#include "Snake.h"

Snake* makeDemoSnake() {
    Snake* ret = new Snake;
    ret->heading = 2;
    ret->s = new SnakeNode(5, 7, 2, SnakeType::HEAD);
    SnakeNode* tail = ret->s;
    tail->next = new SnakeNode(4, 7, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(3, 7, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 7, 3, SnakeType::TURN_RIGHT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 8, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 9, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 10, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 11, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 12, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 13, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 14, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 15, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 16, 3, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(2, 17, 0, SnakeType::TURN_RIGHT);
    tail = tail->next;
    tail->next = new SnakeNode(3, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(4, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(5, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(6, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(7, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(8, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(9, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(10, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(11, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(12, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(13, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(14, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(15, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(16, 17, 0, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 17, 1, SnakeType::TURN_RIGHT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 16, 1, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 15, 1, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 14, 1, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 13, 1, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 12, 1, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(17, 11, 2, SnakeType::TURN_RIGHT);
    tail = tail->next;
    tail->next = new SnakeNode(16, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(15, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(14, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(13, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(12, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(11, 11, 2, SnakeType::DIRECT);
    tail = tail->next;
    tail->next = new SnakeNode(10, 11, 2, SnakeType::TAIL);
    tail = tail->next;
    return ret;
}

funcPtr start() {
    cleardevice();
    BeginBatchDraw();
    setlinecolor(C_WALL);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
    line(10, 10, 10, 430);
    line(10, 10, 430, 10);
    line(430, 10, 430, 430);
    line(10, 430, 430, 430);

    Snake* s = makeDemoSnake();
    draw(s, 1);

    setFont(60);
    setbkmode(TRANSPARENT);
    settextcolor(CT_SNAKE);
    outtextxy(50, 80, L"Play Snake!");

    setFont(60);
    settextcolor(CT_START);
    setlinecolor(CT_START);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 4);
    rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
    outtextxy(2 * (72), 2 * (140), L"START");

    setFont(2 * 20);
    settextcolor(CT_SCORE);
    setlinecolor(CT_SCORE);
    outtextxy(2 * (10), 2 * (225), L"Scores: 0");
    EndBatchDraw();
    while (true) {
        auto msg = GetMouseMsg();
        if (140 <= msg.x and msg.x <= 300 and 2 * 138 <= msg.y and
            msg.y <= 2 * 172) {
            if (msg.uMsg == WM_LBUTTONDOWN) {
                setlinecolor(C_MOUSEDOWN);
                rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2),
                          2 * (170 + 2));
            } else if (msg.uMsg == WM_LBUTTONUP) {
                // Enter main game function.
                return game;
            }
        } else {
            if (msg.uMsg == WM_LBUTTONUP) {
                setlinecolor(CT_START);
                rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2),
                          2 * (170 + 2));
            }
        }
    }
}