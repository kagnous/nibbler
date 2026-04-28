#include "../Includes/Snake.hpp"

Snake::Snake() {} // Constructeur par défaut

Snake::Snake(int startX, int startY) // Constructeur (taille 4 vers droite)
{
    //std::cout << "Création du Snake..." << std::endl;

    _direction = RIGHT;
    for (int i = 0; i < 4; i++) // Ajoute 4 tile au snake pour démarrer
    {
        Position p;
        p.x = startX - i;
        p.y = startY;
        _body.push_back(p);
    }

    //std::cout << "Snake créé" << std::endl;
}

Snake::Snake(const Snake &copy)
{
    *this = copy;
    std::cout << "Mais POURQUOI on fait une copie de Snake ?!?" << std::endl;
}

Snake &Snake::operator=(const Snake &src)
{
    // copier toutes les valeurs de src dans this
    (void)src;
    std::cout << "Mais POURQUOI on fait une égalité avec Snake ?!?" << std::endl;
    return *this;
}

Snake::~Snake() {}

State Snake::move(const std::vector<std::vector<Tile> > &map) // Avance la tête de 1 dans la direction
{
    Position head = _body.front();

    switch(_direction)
    {
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        default:
            std::cout << "WTF j'vais où ?!?" << std::endl;
    }

    switch(map[head.y][head.x])
    {
        case WALL:
            std::cout << "GAME OVER" << std::endl;
            return DEAD;
            break;
        case EMPTY:
            _body.insert(_body.begin(), head);
            _body.pop_back();
			return ALIVE;
            break;
        case SNAKE:
            std::cout << "GAME OVER" << std::endl;
            return DEAD;
            break;
        case FOOD:
            //std::cout << "Nôm nôm nôm..." << std::endl;
            _body.insert(_body.begin(), head);
			return EAT;

            // rappeler placeFood()

            break;
        default:
            std::cout << "PTDR chuis où ???" << std::endl;
			return ALIVE;
            break;
    }
}

void Snake::setDirection(Direction dir)
{
	if ((dir == UP) & (_direction != DOWN))
    	_direction = dir;
	if ((dir == DOWN) & (_direction != UP))
    	_direction = dir;
	if ((dir == RIGHT) & (_direction != LEFT))
    	_direction = dir;
	if ((dir == LEFT) & (_direction != RIGHT))
    	_direction = dir;
}

const std::vector<Position> &Snake::getBody() const
{
    return _body;
}