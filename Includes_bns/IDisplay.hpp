#pragma once

#include <vector>
#include "Types_bns.hpp"

class IDisplay
{
	public:
		virtual void init(int width, int height) = 0;
		virtual void clear() = 0;
		virtual void drawMap(const std::vector<std::vector<Tile>>& map) = 0;
		virtual void display() = 0;

		virtual ~IDisplay() {}

		virtual int getInput() = 0;
};
