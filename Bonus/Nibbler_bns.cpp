#include <iostream>
#include <vector>

#include "../Includes_bns/Game_bns.hpp"

static bool isNumber(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac > 3)
    {
        std::cerr << "Wrong number of argument! Please enter the map name or dimensions." << std::endl;
		exit(1);
    }

    if (ac == 3)
    {
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

        std::cout << "Mode de base" << std::endl;
        Game game(width, height);
        game.run();
    }
    else if (ac == 2)
    {
        std::cout << "Map sélectionnée" << std::endl;
        Game game(av[1]);
        game.run();
    }
    else
         std::cerr << "Please enter the map name or dimensions." << std::endl;

    return 0;
}
