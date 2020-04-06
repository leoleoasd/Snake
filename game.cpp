#include <ctime>
#include <random>
#include "Snake.h"
using namespace std;

typedef int map_t[20][20];

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

void draw_wall(int x, int y) {
    setlinestyle(PS_NULL);
    setfillcolor(C_WALL);
    setlinecolor(C_WALL);
    fillrectangle(x * SNAKE_SIZE + S_OFFSET_X, y * SNAKE_SIZE + S_OFFSET_Y,
                  (x + 1) * SNAKE_SIZE + S_OFFSET_X,
                  (y + 1) * SNAKE_SIZE + S_OFFSET_Y);
}

void draw_food(int x, int y, int dot) {
    static int data[2][10][10] = {{
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  },
                                  {
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
                                      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  }
    };
    for (int i = 0; i < SNAKE_SIZE; ++i) {
        for (int j = 0; j < SNAKE_SIZE; ++j) {
            if (data[dot][i / 2][j / 2])
                putpixel(x * SNAKE_SIZE + S_OFFSET_X + i,
                         y * SNAKE_SIZE + S_OFFSET_Y + j, C_FOOD);
        }
        cout << endl;
    }
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

funcPtr game() {
    for (int i = 0; i < HEIGHT; i += 40) {
        clearrectangle(0, i, WIDTH, i + 40);
        Sleep(20);
    }

    Snake* s = makeStartSnake();
    map_t map{1};
    {
        SnakeNode* t = s->s;
        while (t != nullptr) {
            map[t->x][t->y] = 2;
            t = t->next;
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
    int snake_status = 1;

    setlinecolor(C_WALL);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
    line(10, 10, 10, 430);
    line(10, 10, 430, 10);
    line(430, 10, 430, 430);
    line(10, 430, 430, 430);

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
            snake_status = !snake_status;
            auto [tox, toy] = s->towards();
            if (map[tox][toy] == 1) {
                // DIED!;
                return nullptr;
            }
            eating = (tox == fruit_x and toy == fruit_y);
            SnakeNode* newhead =
                new SnakeNode(tox, toy, s->heading, SnakeType::HEAD);
            newhead->next = s->s;
            if (s->heading == s->s->direction) {
                s->s->type = SnakeType::DIRECT;
            } else {
                if ((s->heading + 3) % 4 == s->s->direction) {
                    s->s->type = SnakeType::TURN_LEFT;
                } else {
                    s->s->type = SnakeType::TURN_RIGHT;
                }
            }
            s->s = newhead;
            if (!eating) {
                int dddd = 0;
                while (newhead->next->next != nullptr) {
                    dddd = newhead->direction;
                    newhead = newhead->next;
                }
                newhead->type = SnakeType::TAIL;
                newhead->direction = dddd;
                map[newhead->next->x][newhead->next->y] = 0;
                delete newhead->next;
                newhead->next = nullptr;
            }
            if (map[tox][toy] == 2) {
                // DIED!;
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
        setlinecolor(C_WALL);
        setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
        line(10, 10, 10, 430);
        line(10, 10, 430, 10);
        line(430, 10, 430, 430);
        line(10, 430, 430, 430);
        draw(s, dot, snake_status);
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
    }
}