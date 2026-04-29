#include <iostream>
#include <vector>

#include "../Includes/Game.hpp"

static bool isNumber(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Wrong number of argument! Please enter height and lenght of the map." << std::endl;
		exit(1);
    }

    if (!isNumber(av[1]) || !isNumber(av[2]))
    {
        std::cerr << "Error: width and height must be numbers" << std::endl;
        return 1;
    }

    int width = std::atoi(av[1]);
    int height = std::atoi(av[2]);

    if (width < 5 || height < 5 || width > 50 || height > 50)
    {
        std::cerr << "Error: invalid map size" << std::endl;
        return 1;
    }

    Game game(width, height);
	game.run();

    return 0;
}
