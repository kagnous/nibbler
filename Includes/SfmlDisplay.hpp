#pragma once

#include "IDisplay.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SfmlDisplay : public IDisplay
{
public:
    SfmlDisplay();
    void init(int width, int height);
    void clear();
    void drawMap(const std::vector<std::vector<Tile>>& map);
    void display();
    int getInput();
	void drawSnake(const std::vector<Position> &body);
    ~SfmlDisplay();

private:
    sf::RenderWindow _window;
    int           _tileSize;
	sf::Texture      _texWall;
    sf::Texture      _texSnake;
    sf::Texture      _texFood;
	sf::Texture		_texHead;
	sf::Texture		_texHead2;
	sf::Texture		_texHead3;
	sf::Texture		_texTail;
	sf::Texture		_texCorner;
    sf::Sprite      _sprite;
	sf::Sprite      _foodSprite;
	sf::Sprite		_bodySprite;
	sf::Sprite		_cornerSprite;
	sf::Clock		_animClock;
	int				_animFrame;
};