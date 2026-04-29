#pragma once

#include "IDisplay.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SfmlDisplay : public IDisplay
{
public:
    SfmlDisplay();
    void init(int width, int height);
    void clear();
    void drawMap(const std::vector<std::vector<Tile>>& map);
    void display();
    int getInput();
    ~SfmlDisplay();

private:
    sf::RenderWindow _window;
    int           _tileSize;
};
