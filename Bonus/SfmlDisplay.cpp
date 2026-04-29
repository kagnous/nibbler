#include "../Includes_bns/SfmlDisplay.hpp"

SfmlDisplay::SfmlDisplay() : _tileSize(32) 
{}

void SfmlDisplay::init(int width, int height)
{
    _window.create(sf::VideoMode(width * _tileSize, height * _tileSize), "Nibbler");
    _window.setFramerateLimit(60);
}

void SfmlDisplay::clear()
{
    _window.clear(sf::Color::Black);
}

void SfmlDisplay::drawMap(const std::vector<std::vector<Tile>>& map)
{
    sf::RectangleShape rect(sf::Vector2f(_tileSize - 1, _tileSize - 1));

    for (int y = 0; y < (int)map.size(); y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {
            switch (map[y][x]) {
                case WALL:  rect.setFillColor(sf::Color(100, 100, 100)); break;
                case SNAKE: rect.setFillColor(sf::Color(0, 200, 0));     break;
                case FOOD:  rect.setFillColor(sf::Color(0, 0, 255));     break;
                default:    rect.setFillColor(sf::Color(20, 20, 20));    break;
            }
            rect.setPosition(x * _tileSize, y * _tileSize);
            _window.draw(rect);
        }
    }
}

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