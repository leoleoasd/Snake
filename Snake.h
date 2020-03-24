#pragma once
#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <iostream>
#include <cstring>

#define SNAKE_SIZE 20

struct funcPtr {
	funcPtr(*next)(void);
	funcPtr operator()() {
		return next();
	}
	funcPtr(funcPtr(*a)(void)) {
		next = a;
	}
};

enum class SnakeType
{
	DIRECT, DIRECT2,TURN, HEAD, TAIL
};

struct Snake
{
	int x;
	int y;

	// 0: <    1: ^    2: >    3: v
	int direction;
	
	// 0: body, 1: turn, 2: head, 3: tail
	SnakeType type = SnakeType::DIRECT;
};

#include "resource.h"
#include "utils.h"

funcPtr start();
funcPtr game();
funcPtr pause();
funcPtr end();
