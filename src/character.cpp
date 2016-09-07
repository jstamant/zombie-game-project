//************************************************
// character.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "character.h"
#include "defines.h"
#include "drawable.h"
#include <math.h>

//DEBUG
#include <iostream>

Character::Character() {
    texture.loadFromFile("character.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
}

Character::Character(int initial_x, int initial_y): Character::Character() {
    set_pos(initial_x, initial_y);
}

void Character::on_notify(Event event) {
    std::cout << "Character notified...\n"; //DEBUG
    switch (event) {
        case SHOOT:
            //shoot
            notify(event);
            break;
        case MOVE_DOWN:
            move_down();
            break;
    }
    std::cout << "Done character notified!\n"; //DEBUG
}

void Character::set_pos(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    sprite.setPosition(x, y);
}

float  Character::get_x(void)     { return sprite.getPosition().x; }
float  Character::get_y(void)     { return sprite.getPosition().y; }
double Character::get_angle(void) { return angle; }

void Character::move_up(void) {
    y -= SPEED;
    set_pos(x, y);
}

void Character::move_down(void) {
    y += SPEED;
    set_pos(x, y);
}

void Character::move_left(void) {
    x -= SPEED;
    set_pos(x, y);
}

void Character::move_right(void) {
    x += SPEED;
    set_pos(x, y);
}

//Rotates the character to face the mouse pointer.
void Character::rotate(void) {
    sf::Vector2i mouse_vector(mouse_->getPosition(*window_));
    sf::Vector2i sprite_vector(sprite.getPosition());
    sf::Vector2i angle_vector(mouse_vector - sprite_vector);
    angle = atan2(angle_vector.y, angle_vector.x) * 180 / PI;
    sprite.setRotation(angle);
}

sf::Sprite Character::get_drawable(void) {
    return sprite;
}

