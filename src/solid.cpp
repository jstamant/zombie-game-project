//************************************************
// solid.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "solid.h"

Solid::Solid() {
    //Added by Joel
    spriteOriginX = 90;
    spriteOriginY = 90;
    spriteWidth = 32;
    spriteHeight = 32;
    set_sprite();
    //

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

