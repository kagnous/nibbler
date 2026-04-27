#pragma once

#include "Nibbler.hpp"

class Snake
{
	private:
	public:
		Snake();
		Snake(const Snake &copy);
		Snake &operator=(const Snake &src);
		~Snake();

		int taille;
		float vitesse;
		std::vector<int> pos;
		enum dir;
}