# Nibbler

A snake-like game built in C++. The main objective here is to use 3 graphical backends compiled as separated shared librairies and to swap at runtime without recompilation needed.

---

## Features

- 3 interchangeable display backends switchable at runtime:
	- **Ncurses** — terminal-based rendering
	- **SDL2** — hardaware-accelerated 2D window
	- **SFML** — sprite-based 2D window with assets
- **Bonus**: custom map loading from a `.txt` file (predefined maps included)

---

## Dependencies

- ncursesw
- SDL2
- SFML

## Build

