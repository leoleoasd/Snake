#include "Snake.h"
using namespace std;

funcPtr game() {
	for (int i = 0; i < HEIGHT; i += 80) {
		clearrectangle(0, i, WIDTH, i + 80);
		cout << "Clearing" << 0 << i << WIDTH << i + 20 << endl;
		Sleep(30);
	}

	setlinecolor(C_WALL);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, (10));
	line(10, 10, 10, 430);
	line(10, 10, 430, 10);
	line(430, 10, 430, 430);
	line(10, 430, 430, 430);
	
	static int dot = 0;
	dot = ~dot;
	Snake *s = new Snake{ 0,0,3,SnakeType::TURN };
	Snake* head = s;
	draw(*s, dot);
	s->next = new Snake{ 0,1,1,SnakeType::DIRECT};
	s = s->next;
	s->next = new Snake{ 0,2,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,3,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,4,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,5,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,6,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,7,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,8,1,SnakeType::DIRECT };
	s = s->next;
	s->next = new Snake{ 0,9,1,SnakeType::DIRECT };
	s = s->next;
	draw(*head, dot);
	_getch();
	return game;
}