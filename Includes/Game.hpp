#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

#include "Types.hpp"

/*enum Tile {
    EMPTY,
    WALL,
    SNAKE,
    FOOD
};*/

#include "Snake.hpp"

class Game
{
    public:
        Game();
        Game(int width, int height);
        Game(const Game &copy);
        Game &operator=(const Game &src);
        ~Game();

        void run();

    private:
        int _width;
        int _height;
        int _frame;
        std::vector<std::vector<Tile> > _map;
        Snake _snake;

        void initMap();
        void placeFood();
        void placeSnake();
        void update();
        void render();  // A REMPLACER PAR LIBRAIRIE DYNAMIQUES
};
