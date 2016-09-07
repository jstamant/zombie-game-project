//************************************************
// drawable.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

#include "drawable.h"

Entity::Entity() : Entity::Entity(0, 0) {
    //Delegating constructors requires a body
}

Entity::Entity(int x, int y) {
    sprite.setPosition(x, y);
}

sf::Sprite Entity::get_sprite(void) {
    return sprite;
}

void Entity::set_window(sf::RenderWindow* window) {
    window_ = window;
}

void Entity::set_mouse(sf::Mouse* mouse) {
    mouse_ = mouse;
}

