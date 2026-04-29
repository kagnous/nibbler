#pragma once

#include "IDisplay.hpp"
#include <SDL2/SDL.h>

class SdlDisplay : public IDisplay
{
public:
    SdlDisplay();
    void init(int width, int height);
    void clear();
    void drawMap(const std::vector<std::vector<Tile>>& map);
    void display();
    int getInput();
    ~SdlDisplay();

private:
    SDL_Window*   _window;
    SDL_Renderer* _renderer;
    int           _tileSize;
};
