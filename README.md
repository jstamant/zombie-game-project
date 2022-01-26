# Zombie Game Project

This game is a 2D top-down zombie-survival game.

Although not yet implemented, the goal is to establish yourself in a
procedurally-generated world filled with zombies. The game's intent is not to
realistically simulate a zombie-apocalypse like Project Zomboid. Rather, its
intent is to provide an amusing amount of action and progression, while
challenging the player dynamically.

# Screenshots

Placeholder section. In its current state, this game does not merit screenshots.

# Current features

This project is still in the early stages of development, and has yet to reach
a playable state. This is more of a placeholder section, but regardless, here's
a list of the main gameplay elements:

* Movement
* Zombies
* ~~Shooting~~
* Health
* ~~Ammunition~~

# Planned features

Actually...I'm planning on changing this entirely from "zombie survival" theme
to "alien-infested-planet survival". Here are some things I'd like to
implement:

* Crafting
* Resource gathering
* Base building
* Vehicles
* Weapon customization
* Procedurally-generated world

# Installation

You can get this to work on Windows if you have some IDE or compiler experience,
but by far the easiest way to try this out is using `make` on Linux.

I believe this game's only dependencies are SDL2 and EnTT. Before installation,
make sure they're installed, then enter the following command in the same
directory as the makefile:

`$ make`

or to build and run the game:

`$ make run`

# Contributing

Since this game is still in its infancy, contributions now will greatly shape
the future of this game. I can see this as an attractive reason to contribute.
Check out
the [issues tracker](https://github.com/jstamant/zombie-game-project/issues) for
programming tasks if it interests you.

But there still exists A LOT of room for improvement. Most notably: the code
base lacks coding standards, although it's
a
[work in progress](https://github.com/jstamant/zombie-game-project/blob/master/README.md) and
the interfaces between classes were poorly planned. As much as I tried keeping
my code organized, because of the huge intake of code to get this going, this
game needs A LOT of refactoring.

I don't have a set workflow yet for this project, although I can say that I use
`git rebase` over `git merge`. If you wish to contribute: please just contact
me over github.

The licensing may be an issue, though. I'm an advocate of open-source software,
and information freedom, but I have to figure out a model or a development plan
for this game. It's currently licensed under the MIT license, but as the sole
contributor, I may change this going forward.

