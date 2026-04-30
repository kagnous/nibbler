#pragma once

#include "IDisplay.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <dlfcn.h>

#include "Types.hpp"
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
		typedef IDisplay* (*CreateFunc)();
		typedef void (*DestroyFunc)(IDisplay*);
        int _width;
        int _height;
        int _frame;
		bool _running;
		void *_handle;
		IDisplay *_display;
		CreateFunc _create;
		DestroyFunc _destroy;
        std::vector<std::vector<Tile> > _map;
        Snake _snake;

        void initMap();
        void placeFood();
        void placeSnake();
        void update();
		void handleInput(int input);
		void loadLib(int input);
		void close();
};
