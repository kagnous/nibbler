#include "IDisplay.hpp"
#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <locale.h>

class NcursesDisplay : public IDisplay {
public:
    void init(int width, int height);
    void clear();
    void drawMap(const std::vector<std::vector<Tile>>& map);
    void display();
    int getInput();
};