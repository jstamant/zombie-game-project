//************************************************
// pickup.cpp
//************************************************

//Include dependencies
#include "pickup.h"

Pickup::Pickup() {
    //Added by Joel
    spriteOriginX = 0;
    spriteOriginY = 99;
    spriteWidth = 32;
    spriteHeight = 32;
    set_sprite();
    //

    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
}

Pickup::Pickup(int x, int y): Pickup::Pickup() {
    set_position(x, y);
}

void Pickup::update_logic(void) {
    //rect_ = sprite_.getGlobalBounds();
}

bool Pickup::is_pickup(void) { return true; }

