# Zombie Game Project

TODO to implement a style guide

This game is a 2D top-down zombie-survival game.

Although not yet implemented, the goal is to establish yourself in a
procedurally-generated world filled with zombies. The game's intent is not to
realistically simulate a zombie-apocalypse like Project Zomboid. Rather, its
intent is to provide an amusing amount of action and progression, while
challenging the player dynamically.

The goal of this project is to build a game in C++, and have it be as portable
as possible (i.e. write once, compile anywhere). For this reason, I'm trying to
stick to portable libraries like SDL2, SDL2_mixer, EnTT, etc.

I just recently moved the code from using SFML to using SDL2. Some of the
gameplay elements I had before are no longer implemented. I've also implemented
EnTT as an ECS instead of using my own custom ECS. EnTT is far superior and
easier to use than the custom ECS I had before.

## Screenshots

![Screenshot](/doc/2022-02-10-135519-scrot.png)

![Screenshot](/doc/2022-02-10-135613-scrot.png)

![Screenshot](/doc/2022-02-10-135615-scrot.png)

## Current features

This project is still in the early stages of development, and has yet to reach
a playable state. This is more of a placeholder section, but regardless, here's
a list of the main gameplay elements:

* Movement
* Zombies
* Shooting
* Health
* Ammunition
* Scrolling view

## Planned features

Here are some of the features I'd like to implement:

* Multiple enemy types
* Crafting
* Resource gathering
* Base building
* Weapon customization
* Procedurally-generated world
* Vehicles

## Installation

As this project is still quite early in development, there are no binary
releases. It must be built from source, using `cmake`.

First, install the game's dependencies:

* [SDL2](https://www.libsdl.org/)
* [SDL_image](https://github.com/libsdl-org/SDL_image)
* [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
* [EnTT](https://github.com/skypjack/entt) >= v3.12.0

Then, generate a makefile using `cmake` from the `build directory`:

```
mkdir build
cd build
cmake ..
```

Finally, you can build the project and run the resulting binary (`sdl-app.out`)
using the following commands:

```
make
make run
```

Running `cmake` will generate the `compile_commands.json` file that your LSP
needs for interpreting the project's translation units.

## Contributing

Since this game is still in its infancy, contributions now will greatly shape
the future of this game. Check out the [issues
tracker](https://github.com/jstamant/zombie-game-project/issues) for programming
tasks if it interests you.

I don't have a set workflow for this project, although I can say that I use `git
rebase` over merging branches. If you wish to contribute, please just contact me
privately or in one of the open issues.
