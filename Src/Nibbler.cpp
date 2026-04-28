#include <iostream>
#include <vector>

#include "../Includes/Game.hpp"

//Création de pointeur de fonction
typedef IDisplay* (*CreateFunc)();
typedef void (*DestroyFunc)(IDisplay*);

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

	//Chargement de la librairie
    void *handle = dlopen("./libsdl_display.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

	//Récupération des fonctions de la librairie
    CreateFunc create = (CreateFunc)dlsym(handle, "createDisplay");
    DestroyFunc destroy = (DestroyFunc)dlsym(handle, "destroyDisplay");

    if (!create || !destroy)
    {
        std::cerr << "dlsym error\n";
        return 1;
    }

    IDisplay* display = create();

    Game game(width, height);
    game.run(display);

	destroy(display);
	dlclose(handle);

    return 0;
}
