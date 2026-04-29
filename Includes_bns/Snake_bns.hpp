#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "Types_bns.hpp"

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

class Snake
{
	private:
		Direction _direction;
		std::vector<Position> _body; // Liste de l'ensemble du corps + tête
	public:
		Snake();
		Snake(int startX, int startY);
		Snake(const Snake &copy);
		Snake &operator=(const Snake &src);
		~Snake();

		void init(int startX, int startY);
		State move(const std::vector<std::vector<Tile> > &map, int width, int height);

		// Setter
		void setDirection(Direction dir);

		// Getter
		const std::vector<Position> &getBody() const;
};
