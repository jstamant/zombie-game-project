//************************************************
// pickup.cpp
//************************************************

//Include dependencies
#include "pickup.h"

Pickup::Pickup() {
    //Added by Joel
    spriteOriginX = 10;
    spriteOriginY = 90;
    spriteWidth = 30;
    spriteHeight = 21;
    set_sprite();
    //

    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
}

Pickup::Pickup(int x, int y): Pickup::Pickup() {
    set_position(x, y);
}

void Pickup::update_logic(void) {
    rect_ = sprite_.getGlobalBounds();
}

bool Pickup::is_pickup(void) { return true; }

