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

### Auto-install dependencies + build
```bash
./setup.sh
```

Runs CMake to detect or download missing libraries, then ask the version of nibbler

### Clean
```bash
make clean	#remove object files
make fclean	#remove object files + binaries
```

---

## Usage

### Standard
```bash
./Nibbler <width> <height>
```

- `width` and `height` must be integers between **5** and **50**

### Bonus
- with dimensions:
```bash
./Nibbler_bonus <width> <height>
```
or

- with custom map:
```bash
./Nibbler_bonus <map_name>.txt
```
Map format: `#` = wall, ` ` = empty, `S` = snake spawn, `*` = food spawn.

Included maps: `Base.txt`, `EasyPacMan.txt`, `PacMAn.txt`

---

## Controls

| Key              | Action                        |
|------------------|-------------------------------|
| Arrow keys       | Move the snake                |
| `2` / `é`        | Switch to SDL2 display        |
| `3` / `"`        | Switch to SFML display        |
| `ESC`            | Quit                          |


