#include "Snake.h"
using namespace std;

funcPtr game() {
	cleardevice();
	setlinecolor(C_WALL);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 20);
	line(10, 10, 10, 430);
	line(10, 10, 430, 10);
	line(430, 10, 430, 430);
	line(10, 430, 430, 430);
	
	static int dot = 0;
	dot = ~dot;
	Snake *s = new Snake{ 0,0,1,SnakeType::DIRECT };
	Snake* head = s;
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
	s->next = new Snake{ 0,9,0,SnakeType::TURN_RIGHT };
	s = s->next;
	s->next = new Snake{ 1,9,3,SnakeType::TURN_LEFT };
	s = s->next;
	s->next = new Snake{ 1,10,0,SnakeType::TURN_RIGHT };
	s = s->next;
	s->next = new Snake{ 2,10,1,SnakeType::TURN_RIGHT };
	s = s->next;
	draw(*head, dot);
	_getch();
	return game;
}