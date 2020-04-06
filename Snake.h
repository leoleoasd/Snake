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

struct SnakeNode {
    int x = 0;
    int y = 0;

    // 0: <    1: ^    2: >    3: v
    int direction = 0;

    // 0: body, 1: turn, 2: head, 3: tail
    SnakeType type = SnakeType::DIRECT;

    SnakeNode* next;

    SnakeNode(int x, int y, int direction, SnakeType type)
        : x(x), y(y), direction(direction), type(type), next(nullptr) {}
};

struct Snake {
    static constexpr int dir[4][2]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    SnakeNode* s;
    int heading;

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

    [[nodiscard]] std::tuple<int, int> towards() const {
        return std::make_tuple((this->s->x + Snake::dir[heading][0] + 20) % 20,
                               (this->s->y + Snake::dir[heading][1] + 20) % 20);
    }
};

#include "resource.h"
#include "utils.h"

funcPtr start();
funcPtr game();
funcPtr end();
