#pragma once

#define WIDTH 440
#define HEIGHT 520
#define S_OFFSET_X 20
#define S_OFFSET_Y 20

extern int colors[][3];
extern int themes_count;
extern int theme_selected;

// Colors
// C for normal colors, CT for text colors.
#define C_BACK (colors[theme_selected][0])
//0x0
#define C_WALL (colors[theme_selected][1])
#define C_MOUSEDOWN 0x0
// SnakeNode body
#define C_SB (colors[theme_selected][2])
// SnakeNode dot
#define C_SD (colors[theme_selected][0])
// Food
#define C_FOOD ((colors[theme_selected][2] + colors[theme_selected][1]) / 2)

#define CT_SNAKE ((colors[theme_selected][2] + 0xffffff - colors[theme_selected][0]) / 2)
#define CT_START \
    ((colors[theme_selected][2] + 0xffffff - colors[theme_selected][0]) / 2)
// 0xffffff
#define CT_SCORE \
    ((colors[theme_selected][2] + 0xffffff - colors[theme_selected][0]) / 2)

#define TIK (int(0.25 * CLOCKS_PER_SEC))
#define DOT_TIK (int(0.125 * CLOCKS_PER_SEC))
