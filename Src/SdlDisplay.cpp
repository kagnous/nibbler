#include "../Includes/SdlDisplay.hpp"

SdlDisplay::SdlDisplay() : _window(nullptr), _renderer(nullptr), _tileSize(32) {}

void SdlDisplay::init(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow("Nibbler",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width * _tileSize, height * _tileSize, 0);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void SdlDisplay::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SdlDisplay::drawMap(const std::vector<std::vector<Tile>>& map)
{
    for (int y = 0; y < (int)map.size(); y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {
            SDL_Rect rect = { x * _tileSize, y * _tileSize, _tileSize, _tileSize };
            switch (map[y][x]) {
                case WALL:
                    SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255); break;
                case SNAKE:
                    SDL_SetRenderDrawColor(_renderer, 0, 200, 0, 255);     break;
                case FOOD:
                    SDL_SetRenderDrawColor(_renderer, 200, 0, 0, 255);     break;
                default:
                    SDL_SetRenderDrawColor(_renderer, 20, 20, 20, 255);    break;
            }
            SDL_RenderFillRect(_renderer, &rect);
        }
    }
}

void SdlDisplay::display()
{
    SDL_RenderPresent(_renderer);
}

int SdlDisplay::getInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return INPUT_QUIT;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:     return INPUT_UP;
                case SDLK_DOWN:   return INPUT_DOWN;
                case SDLK_LEFT:   return INPUT_LEFT;
                case SDLK_RIGHT:  return INPUT_RIGHT;
                case SDLK_ESCAPE: return INPUT_QUIT;
				case SDLK_1:	  return INPUT_LIB1;
				// case SDLK_2:	  return INPUT_LIB2;
				case SDLK_3:	  return INPUT_LIB3;
                default: break;
            }
        }
    }
    return INPUT_NONE;
}

SdlDisplay::~SdlDisplay()
{
    if (_renderer) SDL_DestroyRenderer(_renderer);
    if (_window)   SDL_DestroyWindow(_window);
    SDL_Quit();
}

// Points d'entrée C pour dlopen
extern "C" IDisplay* createDisplay()          { return new SdlDisplay(); }
extern "C" void destroyDisplay(IDisplay* ptr) { delete ptr; }