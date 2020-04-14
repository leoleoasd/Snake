#pragma once

void setFont(int size);

void draw(Snake& s, bool dot);
void draw(Snake* s, bool dot);
void draw_wall(int x, int y);
void draw_food(int x, int y, int dot);