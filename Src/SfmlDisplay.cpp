#include "../Includes/SfmlDisplay.hpp"

SfmlDisplay::SfmlDisplay() : _tileSize(32) 
{}

void SfmlDisplay::init(int width, int height)
{
    _window.create(sf::VideoMode(width * _tileSize, height * _tileSize), "Nibbler");
    _window.setFramerateLimit(60);

	// _texWall.loadFromFile("Assets/wall.png");
    _texSnake.loadFromFile("Assets/body.png");
	_texCorner.loadFromFile("Assets/corner.png");
    // _texFood.loadFromFile("Assets/food.png");
	_texHead.loadFromFile("Assets/headDown.png");
	_texTail.loadFromFile("Assets/tail.png");
	
	// Calculer le scale pour que l'image remplisse exactement un tile
	sf::Vector2u snakeSize  = _texSnake.getSize();
	sf::Vector2u cornerSize = _texCorner.getSize();
	_bodySprite.setScale((float)_tileSize / snakeSize.x, (float)_tileSize / snakeSize.y);
	_bodySprite.setOrigin(snakeSize.x / 2.0f, snakeSize.y / 2.0f);
	_cornerSprite.setScale((float)_tileSize / cornerSize.x, (float)_tileSize / cornerSize.y);
	_cornerSprite.setOrigin(cornerSize.x / 2.0f, cornerSize.y / 2.0f);
	_cornerSprite.setTexture(_texCorner);
	_bodySprite.setTexture(_texSnake);
}

void SfmlDisplay::clear()
{
    _window.clear(sf::Color::Black);
}

void SfmlDisplay::drawSnake(const std::vector<Position> &body)
{
	if (body.empty()) return;
	if (body.size() < 2) return;

    // ── Tête (body[0]) ──────────────────────────────
    int hdx = body[0].x - body[1].x;
    int hdy = body[0].y - body[1].y;

    if(hdx ==  1)
		_sprite.setRotation(270);// va à droite
    else if(hdx == -1)
		_sprite.setRotation(90); 
		  // va à gauche
    else if(hdy ==  1)
		_sprite.setRotation(0);  // va en bas
    else
		_sprite.setRotation(180);    // va en haut

    _sprite.setTexture(_texHead);
	sf::Vector2u s = _texHead.getSize();
	_sprite.setScale((float)_tileSize / s.x, (float)_tileSize / s.y);
	_sprite.setOrigin(s.x / 2.0f, s.y / 2.0f);
    _sprite.setPosition(body[0].x * _tileSize + _tileSize / 2.0f, body[0].y * _tileSize + _tileSize / 2.0f);
    _window.draw(_sprite);
	for (size_t i = 1; i < body.size(); i++)
	{
		// Direction entrante : d'où vient ce segment (segment précédent → ce segment)
		int inX = body[i - 1].x - body[i].x;
		int inY = body[i - 1].y - body[i].y;

		// Direction sortante : où va ce segment (ce segment → segment suivant)
		// Dernier segment : pas de sortante, on réutilise l'entrante
		int outX = (i + 1 < body.size()) ? body[i].x - body[i + 1].x : inX;
		int outY = (i + 1 < body.size()) ? body[i].y - body[i + 1].y : inY;
		
		if (i == body.size()-1) // dessin de la queue
		{
			int tdx = body[i].x - body[i - 1].x;
			int tdy = body[i].y - body[i - 1].y;

			if(tdx ==  1)
				_sprite.setRotation(270);// va à droite
			else if(tdx == -1)
				_sprite.setRotation(90); 
				// va à gauche
			else if(tdy ==  1)
				_sprite.setRotation(0);  // va en bas
			else
				_sprite.setRotation(180);    // va en haut

			_sprite.setTexture(_texTail);
			sf::Vector2u t = _texTail.getSize();
			_sprite.setScale((float)_tileSize / t.x, (float)_tileSize / t.y);
			_sprite.setOrigin(t.x / 2.0f, t.y / 2.0f);
			_sprite.setPosition(body[i].x * _tileSize + _tileSize / 2.0f, body[i].y * _tileSize + _tileSize / 2.0f);
			_window.draw(_sprite);
		}
		else
		{
			bool isCorner = (inX != outX || inY != outY);

			// Rotation selon la combinaison entrée/sortie
			if (!isCorner)
			{
				// Segment droit
				if (inX != 0) 
					_bodySprite.setRotation(90);   // horizontal
				else          
					_bodySprite.setRotation(0);     // vertical
				_bodySprite.setPosition(body[i].x * _tileSize + _tileSize / 2.0f, body[i].y * _tileSize + _tileSize / 2.0f);
				_window.draw(_bodySprite);
			}
			else
			{
				
				// Horizontal in, Vertical out
				if      (inX == -1 && outY == -1) _cornerSprite.setRotation(0);   // LEFT+BOTTOM
				else if (inX == -1 && outY ==  1) _cornerSprite.setRotation(90);  // LEFT+TOP
				else if (inX ==  1 && outY ==  1) _cornerSprite.setRotation(180); // RIGHT+TOP
				else if (inX ==  1 && outY == -1) _cornerSprite.setRotation(270); // RIGHT+BOTTOM
				// Vertical in, Horizontal out (mêmes coins, flux inversé)
				else if (inY ==  1 && outX ==  1) _cornerSprite.setRotation(0);   // BOTTOM+LEFT
				else if (inY == -1 && outX ==  1) _cornerSprite.setRotation(90);  // TOP+LEFT
				else if (inY == -1 && outX == -1) _cornerSprite.setRotation(180); // TOP+RIGHT
				else if (inY ==  1 && outX == -1) _cornerSprite.setRotation(270); // BOTTOM+RIGHT
				_cornerSprite.setPosition(body[i].x * _tileSize + _tileSize / 2.0f, body[i].y * _tileSize + _tileSize / 2.0f);
				_window.draw(_cornerSprite);
			}
		}
	}
}

void SfmlDisplay::drawMap(const std::vector<std::vector<Tile>>& map)
{
    sf::RectangleShape rect(sf::Vector2f(_tileSize - 1, _tileSize - 1));

    for (int y = 0; y < (int)map.size(); y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {
            switch (map[y][x]) {
                case WALL:
					rect.setFillColor(sf::Color(100, 100, 100));
					break;
                case FOOD:
					rect.setFillColor(sf::Color(0, 0, 255));
					break;
                default:
					rect.setFillColor(sf::Color(20, 20, 20));
					break;
            }
            rect.setPosition(x * _tileSize, y * _tileSize);
            _window.draw(rect);
        }
    }
}

// void SfmlDisplay::drawMap(const std::vector<std::vector<Tile>>& map)
// {
//     sf::RectangleShape rect(sf::Vector2f(_tileSize - 1, _tileSize - 1));

//     for (int y = 0; y < (int)map.size(); y++) {
//         for (int x = 0; x < (int)map[y].size(); x++) {
//             switch (map[y][x]) {
//                 case WALL:
// 					rect.setFillColor(sf::Color(100, 100, 100));
// 					break;
//                 case SNAKE:
// 					rect.setFillColor(sf::Color(20, 20, 20));
// 					rect.setPosition(x * _tileSize, y * _tileSize);
//             		_window.draw(rect);
// 					_sprite.setTexture(_texSnake);
// 					_sprite.setPosition(x * _tileSize + _tileSize / 2.0f, y * _tileSize + _tileSize / 2.0f);
//     				_window.draw(_sprite);
// 					continue;
// 				case HEAD:
// 					rect.setFillColor(sf::Color(20, 20, 20));
// 					rect.setPosition(x * _tileSize, y * _tileSize);
//             		_window.draw(rect);
// 					_sprite.setTexture(_texHead);
// 					_sprite.setPosition(x * _tileSize + _tileSize / 2.0f, y * _tileSize + _tileSize / 2.0f);
//     				_window.draw(_sprite);
// 					continue;
//                 case FOOD:
// 					rect.setFillColor(sf::Color(0, 0, 255));
// 					break;
//                 default:
// 					rect.setFillColor(sf::Color(20, 20, 20));
// 					break;
//             }
//             rect.setPosition(x * _tileSize, y * _tileSize);
//             _window.draw(rect);
//         }
//     }
// }

void SfmlDisplay::display()
{
    _window.display();
}

int SfmlDisplay::getInput()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return INPUT_QUIT;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:     return INPUT_UP;
                case sf::Keyboard::Down:   return INPUT_DOWN;
                case sf::Keyboard::Left:   return INPUT_LEFT;
                case sf::Keyboard::Right:  return INPUT_RIGHT;
                case sf::Keyboard::Escape: return INPUT_QUIT;
				case sf::Keyboard::Num1:	return INPUT_LIB1;
				case sf::Keyboard::Num2:	return INPUT_LIB2;
				// case sf::Keyboard::Num3:	return INPUT_LIB3;
                default: break;
            }
        }
    }
    return INPUT_NONE;
}

SfmlDisplay::~SfmlDisplay()
{
    if (_window.isOpen())
        _window.close();
}

extern "C" IDisplay* createDisplay()          { return new SfmlDisplay(); }
extern "C" void destroyDisplay(IDisplay* ptr) { delete ptr; }