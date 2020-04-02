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
	Snake *s = new Snake{ 0,0,3,SnakeType::TURN_LEFT };
	Snake* head = s;
	for(int i = 0; i < 20; ++ i)
	{
		if (i % 2 == 0) {
			if (i != 0) {
				s->next = new Snake{ i,0,3,SnakeType::TURN_LEFT };
				s = s->next;
			}
			for(int j = 1; j < 19; ++ j)
			{
				s->next = new Snake{ i,j,3,SnakeType::DIRECT };
				s = s->next;
			}
			s->next = new Snake{ i,19,0,SnakeType::TURN_RIGHT };
			s = s->next;
		}else
		{
			s->next = new Snake{ i,19,1,SnakeType::TURN_RIGHT };
			s = s->next;
			for (int j = 18; j > 0; --j) {
				s->next = new Snake{ i,j,1,SnakeType::DIRECT };
				s = s->next;
			}
			s->next = new Snake{ i,0,0,SnakeType::TURN_LEFT };
			s = s->next;
		}
	}
	draw(*head, dot);
	_getch();
	return game;
}