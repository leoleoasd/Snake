#pragma once
#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <iostream>
#include <cstring>
#include "resource.h"

struct funcPtr {
	funcPtr(*next)(void);
	funcPtr operator()() {
		return next();
	}
	funcPtr(funcPtr(*a)(void)) {
		next = a;
	}
};

struct snake
{
	int x;
	int y;

	// 0: <    1: ^    2: >    3: v
	int direction;
	
	// 0: body, 1: turn, 2: head, 3: tail
	int type = 0;

	const int DIRECT = 0;
	const int TURN = 1;
	const int HEAD = 2;
	const int TAIL = 3;
};

void setFont(int size);
funcPtr start();
funcPtr game();
funcPtr pause();
funcPtr end();
