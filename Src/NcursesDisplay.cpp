#include "../Includes/NcursesDisplay.hpp"

void NcursesDisplay::init(int width, int height)
{
    (void)width;
    (void)height;

    initscr();              // init ncurses
    noecho();               // pas d'affichage clavier
    cbreak();              // input direct sans enter
    curs_set(0);           // cache curseur
    keypad(stdscr, TRUE);  // flèches
    nodelay(stdscr, TRUE); // input non bloquant
}

void NcursesDisplay::clear()
{
    ::clear();
}

//Affichage de la map
void NcursesDisplay::drawMap(const std::vector<std::vector<Tile>>& map)
{
    for (size_t y = 0; y < map.size(); y++)
	{
        for (size_t x = 0; x < map[y].size(); x++)
		{
            switch (map[y][x])
			{
                case WALL:
                    mvaddch(y, x * 2, '#');
                    break;
                case SNAKE:
                    mvaddch(y, x * 2, 'O');
                    break;
                case FOOD:
                    mvaddch(y, x * 2, '*');
                    break;
                default:
                    mvaddch(y, x * 2, ' ');
                    break;
            }
        }
    }
}

void NcursesDisplay::display()
{
    refresh();
}

//récupération des inputs
int NcursesDisplay::getInput()
{
    int ch = getch();

    switch (ch)
    {
		//Arrow
        case KEY_UP:    return INPUT_UP;
        case KEY_DOWN:  return INPUT_DOWN;
        case KEY_LEFT:  return INPUT_LEFT;
        case KEY_RIGHT: return INPUT_RIGHT;
        case 27:        return INPUT_QUIT; // ESC
        default:        return INPUT_NONE;
    }
}

// Export des fonctions du programme principal vers la librairie
extern "C" IDisplay* createDisplay()
{
    return new NcursesDisplay();
}

extern "C" void destroyDisplay(IDisplay* ptr)
{
    delete ptr;
	endwin();
}
