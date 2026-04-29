#include "../Includes/NcursesDisplay.hpp"

void NcursesDisplay::init(int width, int height)
{
    (void)width;
    (void)height;
	setlocale(LC_ALL, "");
    initscr();              // init ncurses
    noecho();               // pas d'affichage clavier
    cbreak();              // input direct sans enter
    curs_set(0);           // cache curseur
    keypad(stdscr, TRUE);  // flèches
    nodelay(stdscr, TRUE); // input non bloquant
	flushinp();			   // vide le buffer au demarrage
	start_color();
	init_pair(1, COLOR_WHITE,   COLOR_BLACK);  // WALL
	init_pair(2, COLOR_GREEN,   COLOR_BLACK);  // SNAKE
	init_pair(3, COLOR_CYAN,    COLOR_BLACK);  // HEAD
	init_pair(4, COLOR_RED,     COLOR_BLACK);  // FOOD
}

void NcursesDisplay::clear()
{
    ::clear();
}

void NcursesDisplay::drawSnake(const std::vector<Position> &body)
{
	(void)body;
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
				{
					attron(COLOR_PAIR(1));
                    mvaddch(y, x * 2, '#');
					attroff(COLOR_PAIR(1));
                    break;
				}
                case SNAKE:
				{
					attron(COLOR_PAIR(2));
					mvaddch(y, x * 2, 'O');
					attroff(COLOR_PAIR(2));
					break;
				}
				case HEAD:
				{
					attron(COLOR_PAIR(3) | A_BOLD);
					mvaddch(y, x * 2, '@');
					attroff(COLOR_PAIR(3) | A_BOLD);
					break;
				}
				case FOOD:
				{
					attron(COLOR_PAIR(4) | A_BLINK);
					mvaddch(y, x * 2, '*');
					attroff(COLOR_PAIR(4) | A_BLINK);
					break;
				}
				default:
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
    wint_t ch, last = 0;

    // Vide le buffer, garde le dernier
    while (get_wch(&ch) != ERR)
        last = ch;

    switch (last)
    {
		//Arrow
        case KEY_UP:    return INPUT_UP;
        case KEY_DOWN:  return INPUT_DOWN;
        case KEY_LEFT:  return INPUT_LEFT;
        case KEY_RIGHT: return INPUT_RIGHT;
        case 27:        return INPUT_QUIT; // ESC
		// case '1':		return INPUT_LIB1;
		// case L'&':		return INPUT_LIB1; // &
		case '2':		return INPUT_LIB2;
		case L'é':		return INPUT_LIB2; // é
		case '3':		return INPUT_LIB3;
		case L'"':		return INPUT_LIB3; // "
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
