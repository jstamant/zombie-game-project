//************************************************
// character.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "defines.h"
#include "entity.h"
#include "entitymanager.h"
#include <math.h>
//#include "observer.h"
//#include "subject.h"

//DEBUG
//#include <iostream>

Character::Character() {
    texture.loadFromFile("character.png"); //Needs optimizing...
    sprite_.setTexture(texture);
    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
}

Character::Character(int initial_x, int initial_y): Character::Character() {
    set_pos(initial_x, initial_y);
}

void Character::set_pos(int new_x, int new_y) {
    x_ = new_x;
    y_ = new_y;
    sprite_.setPosition(x_, y_);
}

float  Character::get_x(void)     { return sprite_.getPosition().x; }
float  Character::get_y(void)     { return sprite_.getPosition().y; }
double Character::get_angle(void) { return angle; }

void Character::move_up(void) {
    y_ -= SPEED;
    set_pos(x_, y_);
}

void Character::move_down(void) {
    y_ += SPEED;
    set_pos(x_, y_);
}

void Character::move_left(void) {
    x_ -= SPEED;
    set_pos(x_, y_);
}

void Character::move_right(void) {
    x_ += SPEED;
    set_pos(x_, y_);
}

/* Rotates the character to face the mouse pointer.
 */
void Character::rotate(void) {
    sf::Vector2i mouse_vector(mouse_->getPosition(*window_));
    sf::Vector2i sprite_vector(sprite_.getPosition());
    sf::Vector2i angle_vector(mouse_vector - sprite_vector);
    angle = atan2(angle_vector.y, angle_vector.x) * 180 / PI;
    sprite_.setRotation(angle);
}

void Character::shoot(void) {
    sf::Vector2f mouse_position(mouse_->getPosition(*window_));
    Bullet* bullet = new Bullet(sprite_.getPosition(), mouse_position);
    entitymanager_->new_entity(bullet);
}

void Character::update_logic(void) {
    if (mouse_ && window_) {
        rotate();
    }
}

bool Character::is_character(void) { return true; }

