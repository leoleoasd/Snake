#include <ctime>
#include <random>

#include <locale>
#include <codecvt>
#include <fstream>

#include "Snake.h"
using namespace std;
int cur_x;
int cur_y;

Snake* makeStartSnake() {
    Snake* ret = new Snake;
    ret->heading = 0;
    ret->s = new SnakeNode(8, 9, 0, SnakeType::HEAD, nullptr);
    SnakeNode* tail = ret->s;
    tail->next = new SnakeNode(9, 9, 0, SnakeType::DIRECT, tail);
    tail = tail->next;
    tail->next = new SnakeNode(10, 9, 0, SnakeType::DIRECT, tail);
    tail = tail->next;
    tail->next = new SnakeNode(11, 9, 0, SnakeType::DIRECT, tail);
    tail = tail->next;
    tail->next = new SnakeNode(12, 9, 0, SnakeType::TAIL, tail);
    tail = tail->next;
    ret->size = 5;
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
    while (key_queue.size() == 0)
        ;
    key_queue.pop();
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
    settextcolor(CT_START);

    
    //std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> conv1(
    //    new std::codecvt_byname<wchar_t, char, mbstate_t>(
    //        ".936"));
    char_queue = queue<wchar_t>(); // Clear queue;
    while (true) {
        int flag = 0;
        while (!char_queue.empty()) {
            wchar_t c = char_queue.front();
            char_queue.pop();
            if (name.size() < 20) {
                if (!iswcntrl(c)) {
                    name = name + c;
                }
            }
        }
        while (key_queue.size()) {
            int key = key_queue.front();
            key_queue.pop();
            if (name.size() > 0) {
                if (key == VK_BACK) {
                    cout << "DELETING";
                    name = name.substr(0, name.size() - 1);
                }
            }
            if (key == VK_RETURN) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            break;
        }

        BeginBatchDraw();
        cleardevice();
        setFont(60);
        outtextxy(85, 20, L"YOU DIED!");
        outtextxy(70, 90, output.c_str());

        setFont(30);
        moveto(50, 160);
        outtext((L"Name:" + name).c_str());
        cur_x = getx();
        cur_y = gety();
        EndBatchDraw();
    }
    wstring rk_names[5];
    int rk_scores[5] = {0};
    ifstream fin;
    fin.open("data.dat", ios::in);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    if (fin) {
        string tmp;
        int pos = 0;
        while (fin >> tmp) {
            rk_names[pos] = conv.from_bytes(tmp);
            fin >> rk_scores[pos++];
            if (pos >= 4)
                break;
        }
    }
    fin.close();

    for (int i = 0; i < 5; ++i) {
        if (rk_scores[i] < scores) {
            for (int j = 4; j >= i; --j) {
                rk_scores[j] = rk_scores[j - 1];
                rk_names[j] = rk_names[j - 1];
            }
            rk_scores[i] = scores;
            rk_names[i] = name;
            break;
        }
    }
    BeginBatchDraw();
    cleardevice();
    setFont(60);
    outtextxy(85, 20, L"YOU DIED!");
    outtextxy(70, 90, output.c_str());

    setFont(30);
    outtextxy(50, 160, L"RANK:");
    EndBatchDraw();
    for (int i = 0; i < 5; ++i) {
        if (rk_names[i].size()) {
            setFont(30);
            outtextxy(50, 200 + 35 * i,
                      (to_wstring(i + 1) + L"." + rk_names[i] + L": " +
                       to_wstring(rk_scores[i]))
                          .c_str());
        } else {
            break;
        }
    }

    ofstream fout;
    fout.open("data.dat");
    if (fout) {
        for (int i = 0; i < 5; ++i) {
            if (rk_names[i].size()) {
                auto s = conv.to_bytes(rk_names[i]);
                fout.write(s.c_str(), s.size());
                fout << " ";
                fout << rk_scores[i];
                fout << "\n";
            } else {
                break;
            }
        }
    }
    fout.close();
    while (key_queue.size() == 0) {
        Sleep(20);
    }
    key_queue.pop();
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
        for (int i = 0; i < 20; ++ i)
            for (int j = 0; j < 20; ++j) {
                map[i][j] = maps[map_selected][i][j];
            }
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

    int hit_wall = 0;
    int hit_body = 0;
    int hit_x = 0;
    int hit_y = 0;

    
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"play game repeat", NULL, 0, NULL);
    key_queue = queue<int>();
    while (true) {
        // Keyboard Event Handling.
        eating = 0;
        moving = 0;
        if (key_queue.size()) {
            int key = key_queue.front();
            key_queue.pop();
            switch (key) {
                case VK_ESCAPE:
                    pause_game();
                    continue;
                case VK_UP:
                    if (s->heading == 3)
                        moving = 1;
                    if (s->heading == 0 or s->heading == 2) {
                        cout << "Turing up" << endl;
                        s->heading = 3;
                        moving = 1;
                    }
                    break;
                case VK_DOWN:
                    if (s->heading == 1)
                        moving = 1;
                    if (s->heading == 0 or s->heading == 2) {
                        cout << "Turing down" << endl;
                        s->heading = 1;
                        moving = 1;
                    }
                    break;
                case VK_LEFT:
                    if (s->heading == 0)
                        moving = 1;
                    if (s->heading == 1 or s->heading == 3) {
                        cout << "Turing left" << endl;
                        s->heading = 0;
                        moving = 1;
                    }
                    break;
                case VK_RIGHT:
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
                hit_wall = 1;
                hit_x = s->s->x;
                hit_y = s->s->y;
                break;
            }
            eating = (tox == fruit_x and toy == fruit_y);
            auto [tx,ty] = s->move(eating);
            map[tx][ty] = 0;
            if (map[tox][toy] == 2) {
                hit_body = 1;
                hit_x = s->s->x;
                hit_y = s->s->y;
                break;
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
    }

    mciSendString(L"stop game", NULL, 0, NULL);

    time_t duration = (1000.0 / s->size + 1);

    if (hit_wall) {
        while (s->s != nullptr) {

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
            SnakeNode* last = s->s;
            s->s = s->s->next;
            delete last;
            s->status = !s->status;
            Sleep(duration);
        }
    } else {
        SnakeNode *curh, *curt;
        curh = s->s;
        int i = 0;
        while (1) {
            curh = curh->next;
            curt = curh->next;
            if (curh->x == hit_x and curh->y == hit_y) {
                break;
            }
            if (curh == nullptr) {
                break;
            }
        }
        int flag1 = 0;
        int flag2 = 0;
        while (!(flag1 and curt == nullptr)) {
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
            outtextxy(2 * (10), 2 * (225),
                      (wstring{L"Scores: "} + to_wstring(score)).c_str());
            EndBatchDraw();

            if (curt != nullptr) {
                if (flag1) {
                    s->s = curt->next;
                    delete curt;
                    curt = s->s;
                    curt and (curt->last = nullptr);
                } else {
                    SnakeNode* t = curt->next;
                    delete curt;
                    curt = t;
                    curh->next = curt;
                    if (curt) {
                        curt->last = curh;
                    }
                }
            }
            if (!flag1 and curh != nullptr) {
                if (curh->last != nullptr) {
                    curh = curh->last;
                    delete curh->next;
                    curh->next = curt;
                    if (curt) {
                        curt->last = curh;
                    }
                } else {
                    flag1 = 1;
                    s->s = curh->next;
                    curh->next && (curh->next->last = nullptr);
                    delete curh;
                }
            }
            Sleep(duration);
        }
    }
    end_game(score);
    return start;
}