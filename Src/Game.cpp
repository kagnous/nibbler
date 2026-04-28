#include "../Includes/Game.hpp"

Game::Game() { } // Constructeur par défaut

Game::Game(int width, int height) : _snake(width / 2, height / 2) // Constructeur
{
    _width = width;
    _height = height;
	_running = true;
    _frame = 0;
    initMap();

	placeSnake();
    placeFood(); // <= Vérifier que le 1er spawn pas sur le Snake
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

void Game::placeFood() // Place un FOOD sur un EMPTY aléatoire (boucle jusqu'à réussir)
{
    //_map[7][5] = FOOD;
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
	// std::cout << "Food placed" << std::endl;
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
    State state = _snake.move(_map);
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
    //std::cout << "Snake moved" << std::endl;
    //std::cout << "Snake placed" << std::endl;
}

void Game::run(IDisplay *display) // fait tourner le jeu
{
    if (!display)
        return;

    display->init(_width, _height);

    while (_running)
    {

		
		int input = display->getInput();
		
		handleInput(input);
		
        update();

		display->clear();
		display->drawMap(_map);
		display->display();

        usleep(200000);
    }
}
