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

//DEBUG
#include <iostream>

Character::Character(){
    spriteOriginX = 0;
    spriteOriginY = 0;
    spriteWidth = 32;
    spriteHeight = 32;
    set_sprite();

    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
    ammo_ = 10;
    m_health = 100;
}

Character::Character(int x, int y): Character::Character() {
    set_position(x, y);
}

float  Character::get_x(void)     { return sprite_.getPosition().x; }
float  Character::get_y(void)     { return sprite_.getPosition().y; }
//double Character::get_angle(void) { return angle; }

/* Rotates the character to face the mouse pointer.
 */
void Character::rotate(void) {
    sf::Vector2i mouse_vector(mouse_->getPosition(*window_));
    sf::Vector2i sprite_vector(sprite_.getPosition());
    sf::Vector2i angle_vector(mouse_vector - sprite_vector);
    angle_ = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
    sprite_.setRotation(angle_);
}

/* Generates a bullet, and passes it to the entity manager for tracking.
 */
void Character::shoot(void) {
    if (ammo_ > 0)
    {
        sf::Vector2f mouse_position(mouse_->getPosition(*window_));
        Bullet* bullet = new Bullet(sprite_.getPosition(), mouse_position);
        entitymanager_->new_entity(bullet);
        ammo_--;
    }
}

void Character::update_logic(void)
{
    if (mouse_ && window_) {
        rotate();
    }
    if (m_health <= 0) {
        kill();
    }
}

bool Character::is_character(void) { return true; }
bool Character::is_collidable(void) { return true; }

int Character::getAmmo(void) { return ammo_; }
void Character::setAmmo(int ammo) { ammo_ = ammo; }
