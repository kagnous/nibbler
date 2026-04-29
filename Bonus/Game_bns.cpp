#include "../Includes_bns/Game_bns.hpp"

Game::Game() { } // Constructeur par défaut

Game::Game(int width, int height) : _snake(width / 2, height / 2) // Constructeur de map vide
{
    _width = width;
    _height = height;
	_running = false;
	_handle  = nullptr;
	_display = nullptr;
    _frame = 0;
    initMap();

	placeSnake();
    placeFood();
}

Game::Game(const std::string &mapFile) : _snake(-1, -1)// Constructeur de map prédéfinie
{
	_running = false;
	_handle  = nullptr;
	_display = nullptr;
    _frame = 0;
    initMap(mapFile);

	placeSnake();
    std::cout << "Construteur OK" << std::endl;
}

Game::Game(const Game &copy) // Constructeur de copie (canonique oblige)
{
    *this = copy;
    std::cout << "Mais POURQUOI on fait une copie de Game ?!?" << std::endl;
}

Game &Game::operator=(const Game &src) // Opérateur d'égalité (canonique oblige)
{
    // copier toutes les valeurs de src dans this
    this->_width = src._width;
    std::cout << "Mais POURQUOI on fait une égalité avec Game ?!?" << std::endl;
    return *this;
}

Game::~Game() { } // Destructeur

//Chargement de la librairie selon input
void Game::loadLib(int lib)
{
	if (_display)
	{
		_destroy(_display);
		_display = nullptr;
	}
	if (_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
	switch(lib)
	{
		case INPUT_LIB1:
			 _handle = dlopen("./libncurses_display.so", RTLD_LAZY);
			 break;
		case INPUT_LIB2:
			_handle = dlopen("./libsdl_display.so", RTLD_LAZY);
			break;
		case INPUT_LIB3:
			_handle = dlopen("./libsfml_display.so", RTLD_LAZY);
			break;
		default:
			break;
	}
	//Chargement de la librairie
    if (!_handle)
    {
        std::cerr << dlerror() << std::endl;
		 _running = false;
        return;
    }

	//Récupération des fonctions de la librairie
    _create = (CreateFunc)dlsym(_handle, "createDisplay");
    _destroy = (DestroyFunc)dlsym(_handle, "destroyDisplay");

    if (!_create || !_destroy)
    {
        std::cerr << "dlsym error" << std::endl;
		_running = false;
        return;
    }

    _display = _create();
	_display->init(_width, _height);
	_running = true;
}

void Game::close()
{
	if (_display)
	{
		_destroy(_display);
		_display = nullptr;
	}
	if (_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
	std::cout << "Game over!" << std::endl;
}

void Game::initMap() // Remplit la map de EMPTY avec des WALL sur les extrémités
{
    _map.resize(_height, std::vector<Tile>(_width, EMPTY));

    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            if (y == 0 || y == _height - 1 || x == 0 || x == _width - 1)
                _map[y][x] = WALL;
        }
    }
}

#include <filesystem>
void Game::initMap(const std::string &mapFile) // Surcharge pour gérer les map préfaites
{
    std::string path = "Bonus/Maps/" + mapFile;
    std::cout << path << std::endl;

    std::ifstream file(path.c_str());
    if (!file)
        throw std::runtime_error("Cannot open map file");

    std::string line;
    int y = 0;

    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        std::vector<Tile> row;

        for (int x = 0; x < (int)line.size(); x++)
        {
            switch (line[x])
            {
                case '#':
                    row.push_back(WALL);
                    break;

                case ' ':
                    row.push_back(EMPTY);
                    break;

                case '*':
                    row.push_back(FOOD);
                    break;

                case 'S':
                    row.push_back(EMPTY);
                    _snake.init(x, y); // Replace le snake au départ prévu
                    break;

                default:
                    throw std::runtime_error("Invalid character in map");
            }
        }

        _map.push_back(row);
        y++;
    }

    std::cout << "Map chargée" << std::endl;

    // dimensions déduites automatiquement
    _height = _map.size();
    if (_height == 0)
        throw std::runtime_error("Empty map");

    _width = _map[0].size();

    // vérification rectangulaire
    for (size_t i = 0; i < _map.size(); i++)
    {
        if (_map[i].size() != (size_t)_width)
            throw std::runtime_error("Map is not rectangular");
    }
    std::cout << "Map validée" << std::endl;
}

void Game::placeFood() // Place un FOOD sur un EMPTY aléatoire (boucle jusqu'à réussir)
{
    while(1)
    {
        int x = rand() % _width;
        int y = rand() % _height;

        if (_map[y][x] == EMPTY)
        {
            _map[y][x] = FOOD;
            break;
        }
    }
}

void Game::placeSnake() // Met à jour SNAKE dans la map
{
    // Nettoye les anciennes positions du snake
    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            if (_map[y][x] == SNAKE)
                _map[y][x] = EMPTY;
        }
    }

    const std::vector<Position> &body = _snake.getBody();

    // Place le snake dans la map
    for (size_t i = 0; i < body.size(); i++)
    {
        int x = body[i].x;
        int y = body[i].y;

        if (y >= 0 && y < _height && x >= 0 && x < _width)
            _map[y][x] = SNAKE;
    }
}
//Gestions du comportement des inputs
void Game::handleInput(int input)
{
    switch (input)
    {
        case INPUT_UP:
            _snake.setDirection(UP);
            break;
        case INPUT_DOWN:
            _snake.setDirection(DOWN);
            break;
        case INPUT_LEFT:
            _snake.setDirection(LEFT);
            break;
        case INPUT_RIGHT:
            _snake.setDirection(RIGHT);
            break;
        case INPUT_QUIT:
            _running = false;
        default:
            break;
    }
}

void Game::update()
{
    State state = _snake.move(_map, _width, _height);
	placeSnake();
	switch(state)
	{
		case DEAD:
			_running = false;
			break;
		case EAT:
			placeFood();
			break;
		default:
			break;
	}
}

void Game::run()
{
	loadLib(INPUT_LIB1); //charge la librairie par default (ncurses)
    std::cout << "Top départ" << std::endl;
    while (_running)
    {
		
		int input = _display->getInput();
		
		handleInput(input);
		
        update();

		_display->clear();
		_display->drawMap(_map);
		_display->display();

        usleep(500000);
		if (input == INPUT_LIB1 || input == INPUT_LIB2 || input == INPUT_LIB3)
			loadLib(input);
    }
	close();
}
