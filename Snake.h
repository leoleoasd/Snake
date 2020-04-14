#pragma once
#include <conio.h>
#include <easyx.h>  // 引用图形库头文件

#include <cstring>
#include <iostream>
#include <tuple>
#include <string>

#define SNAKE_SIZE 20

struct funcPtr {
    funcPtr (*next)(void);
    funcPtr operator()() { return next(); }
    funcPtr(funcPtr (*a)(void)) { next = a; }
    bool operator!=(const void* another) const { return this->next != another; }
};

enum class SnakeType { DIRECT, TURN_LEFT, TURN_RIGHT, HEAD, TAIL };
typedef int map_t[20][20];
extern map_t maps[];
extern int maps_count;
extern int map_selected;


struct SnakeNode {
    int x = 0;
    int y = 0;

    // 0: <    1: ^    2: >    3: v
    int direction = 0;

    // 0: body, 1: turn, 2: head, 3: tail
    SnakeType type = SnakeType::DIRECT;

    SnakeNode* next;
    SnakeNode* last;

    SnakeNode(int x, int y, int direction, SnakeType type,SnakeNode* last)
        : x(x), y(y), direction(direction), type(type), next(nullptr), last(last) {}
};

struct Snake {
    static constexpr int dir[4][2]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    SnakeNode* s;
    int heading;
    int status = 1;

    Snake() : s(nullptr), heading(0) {}

    ~Snake() {
        auto cur = this->s;
        while (cur != nullptr) {
            auto last = cur;
            cur = cur->next;
            delete last;
        }
    }

    void turn_left() { this->heading = (this->heading + 1) % 4; }

    void turn_right() { this->heading = (this->heading + 3) % 4; }

    std::tuple<int, int> towards() const {
        return std::make_tuple((this->s->x + Snake::dir[heading][0] + 20) % 20,
                               (this->s->y + Snake::dir[heading][1] + 20) % 20);
    }

    std::tuple<int, int> move(int eating) {
        status = !status;
        auto [tox, toy] = this->towards();
        SnakeNode* newhead =
            new SnakeNode(tox, toy, this->heading, SnakeType::HEAD, nullptr);
        newhead->next = this->s;
        this->s->last = newhead;
        if (this->heading == this->s->direction) {
            this->s->type = SnakeType::DIRECT;
        } else {
            if ((this->heading + 3) % 4 == this->s->direction) {
                this->s->type = SnakeType::TURN_LEFT;
            } else {
                this->s->type = SnakeType::TURN_RIGHT;
            }
        }
        this->s = newhead;
        int retx = 0;
        int rety = 0;
        if (!eating) {
            while (newhead->next != nullptr) {
                newhead = newhead->next;
            }
            newhead->last->type = SnakeType::TAIL;
            newhead->last->direction = newhead->last->last->direction;
            retx = newhead->x;
            rety = newhead->y;
            newhead->last->next = nullptr;
            delete newhead;
        }
        return std::make_tuple(retx, rety);
    }
};

#include "resource.h"
#include "rendering.h"

funcPtr start();
funcPtr game();
funcPtr end();
