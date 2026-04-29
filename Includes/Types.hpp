#pragma once

enum Tile {
    EMPTY,
    WALL,
    SNAKE,
	HEAD,
    FOOD
};

enum Input {
    INPUT_NONE,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_QUIT,
	INPUT_LIB1,
    INPUT_LIB2,
    INPUT_LIB3
};

enum State {
	DEAD,
	EAT,
	ALIVE
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Position {
	int x;
	int y;
};
