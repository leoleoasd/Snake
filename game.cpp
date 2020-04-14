#include <ctime>
#include <random>
#include "Snake.h"
using namespace std;

Snake* makeStartSnake() {
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

tuple<int, int> make_fruit(map_t map) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 19);
    
    while (true) {
        int x = dis(gen);
        int y = dis(gen);
        if (map[x][y] == 0) {
            return make_tuple(x, y);
        }
    }
}

void pause_game() {
    cleardevice();
    setFont(60);
    settextcolor(CT_START);
    setlinecolor(CT_START);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 4);
    rectangle(2 * (72 - 2), 2 * (140 - 2), 2 * (148 + 2), 2 * (170 + 2));
    outtextxy(2 * (72), 2 * (140), L"PAUSE");
    _getch();
    cleardevice();
}

void end_game(int scores) {
    for (int i = 0; i < HEIGHT; i += 40) {
        clearrectangle(0, i, WIDTH, i + 40);
        Sleep(20);
    }
    wstring output = L"Scores: ";
    wstring name = L"";
    output += to_wstring(scores);
    setFont(60);
    settextcolor(CT_START);
    outtextxy(85,  10, L"YOU DIED!");
    outtextxy(70, 70, output.c_str());

    setFont(30);
    outtextxy(50, 120, (L"Name:" + name).c_str());
    _getch();
}

funcPtr game() {
    for (int i = 0; i < HEIGHT; i += 40) {
        clearrectangle(0, i, WIDTH, i + 40);
        Sleep(20);
    }

    Snake* s = makeStartSnake();
    map_t map{};
    {
        SnakeNode* t = s->s;
        while (t != nullptr) {
            map[t->x][t->y] = 2;
            t = t->next;
        }
        for (int i = 0; i < 20; ++ i)
            for (int j = 0; j < 20; ++j) {
                map[i][j] = maps[map_selected][i][j];
            }
    }
    int fruit_x = 7;
    int fruit_y = 9;

    int eating = 0;
    int moving = 0;
    int dot = 1;
    clock_t t = clock();
    clock_t d = t;
    int score = 0;

    
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"play game repeat", NULL, 0, NULL);

    while (true) {
        // Keyboard Event Handling.
        eating = 0;
        moving = 0;
        if (_kbhit()) {
            auto key = _getch();
            switch (key) {
                case 27:
                    pause_game();
                    continue;
                    break;
                case KEY_UP:
                    if (s->heading == 3)
                        moving = 1;
                    if (s->heading == 0 or s->heading == 2) {
                        cout << "Turing up" << endl;
                        s->heading = 3;
                        moving = 1;
                    }
                    break;
                case KEY_DOWN:
                    if (s->heading == 1)
                        moving = 1;
                    if (s->heading == 0 or s->heading == 2) {
                        cout << "Turing down" << endl;
                        s->heading = 1;
                        moving = 1;
                    }
                    break;
                case KEY_LEFT:
                    if (s->heading == 0)
                        moving = 1;
                    if (s->heading == 1 or s->heading == 3) {
                        cout << "Turing left" << endl;
                        s->heading = 0;
                        moving = 1;
                    }
                    break;
                case KEY_RIGHT:
                    if (s->heading == 2)
                        moving = 1;
                    if (s->heading == 1 or s->heading == 3) {
                        cout << "Turing right" << endl;
                        s->heading = 2;
                        moving = 1;
                    }
                    break;
            }
        }

        // Move snake if needed.
        if ((clock() - t) > TIK or moving) {
            t = clock();
            auto [tox, toy] = s->towards();
            if (map[tox][toy] == 1) {
                end_game(score);
                return nullptr;
            }
            eating = (tox == fruit_x and toy == fruit_y);
            auto [tx,ty] = s->move(eating);
            map[tx][ty] = 0;
            if (map[tox][toy] == 2) {
                // DIED!;
                end_game(score);
                return nullptr;
            }
            map[tox][toy] = 2;

            if (eating) {
                tie(fruit_x, fruit_y) = make_fruit(map);
                score += 20;
            }
        }

        // Drawing.
        if (clock() - d >= DOT_TIK) {
            d = clock();
            dot = !dot;
        }
        BeginBatchDraw();
        cleardevice();
        setlinecolor(C_SB);
        setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
        line(10, 10, 10, 430);
        line(10, 10, 430, 10);
        line(430, 10, 430, 430);
        line(10, 430, 430, 430);
        draw(s, dot);
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (map[i][j] == 1) {
                    draw_wall(i, j);
                }
            }
        }
        draw_food(fruit_x, fruit_y, dot);
        setFont(40);
        settextcolor(CT_SCORE);
        setlinecolor(CT_SCORE);
        outtextxy(2 * (10), 2 * (225), (wstring{L"Scores: "} + to_wstring(score)).c_str());
        EndBatchDraw();

        Sleep(20);
    }
}