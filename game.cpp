#include "Snake.h"
using namespace std;

funcPtr game() {
	for (int i = 0; i < HEIGHT; i += 20) {
		clearrectangle(0, i, WIDTH, i + 20);
		cout << "Clearing" << 0 << i << WIDTH << i + 20 << endl;
		Sleep(30);
	}
	for (int i = 0; i < 4; i += 1) {
		draw(Snake{ 0,i,i,SnakeType::TURN });
		Sleep(1000);
	}
	_getch();
	return pause;
}