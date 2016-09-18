//************************************************
// solid.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "solid.h"

Solid::Solid() {
    texture.loadFromFile("wall.png"); //Needs optimizing...
    sprite_.setTexture(texture);
    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
}

Solid::Solid(int x, int y): Solid::Solid() {
    set_position(x, y);
}

void Solid::update_logic(void) {

}

bool Solid::is_collidable(void) { return true; }
bool Solid::is_solid(void)      { return true; }

