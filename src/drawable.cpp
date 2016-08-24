//drawable.cpp

//Include SFML dependencies
#include <SFML/Graphics.hpp>

#include "drawable.h"

Drawable::Drawable() : Drawable::Drawable(0, 0) {
    //Delegating constructors requires a body
}

Drawable::Drawable(int x, int y) {
    sprite.setPosition(x, y);
}

sf::Sprite Drawable::get_sprite(void) {
    return sprite;
}

