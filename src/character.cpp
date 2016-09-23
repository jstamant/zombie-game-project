//******************************************************************************
// character.cpp
//******************************************************************************

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

//TEMPORARY
extern sf::View globalView;

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

//******************************************************************************
// Access functions
//******************************************************************************

int   Character::getAmmo(void)     { return ammo_; }
float Character::get_x(void)       { return sprite_.getPosition().x; }
float Character::get_y(void)       { return sprite_.getPosition().y; }

void  Character::setAmmo(int ammo) { ammo_ = ammo; }

//******************************************************************************
// Update functions
//******************************************************************************

/* Rotates the character to face the mouse pointer.
 * TODO use the entity's members for calculations. No need to refer to the
 * sprite.
 */
void Character::rotate(void) {
    sf::Vector2f mousePosition = findMouseCoords();
    sf::Vector2f position = get_position();
    sf::Vector2f angle_vector(mousePosition- position);
    angle_ = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
    sprite_.setRotation(angle_);
}

/* Generates a bullet, and passes it to the entity manager for tracking.
 */
void Character::shoot(void) {
    sf::Vector2f mousePosition;
    Bullet* bullet;
    if (ammo_ > 0)
    {
        mousePosition = findMouseCoords();
        bullet = new Bullet(sprite_.getPosition(), mousePosition);
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
    globalView.setCenter(x_, y_);
}

//******************************************************************************
// Entity-type checking functions
//******************************************************************************

bool Character::is_character(void)  { return true; }
bool Character::is_collidable(void) { return true; }

//******************************************************************************
// General-purpose functions
//******************************************************************************

sf::Vector2f Character::findMouseCoords(void) {
    sf::Vector2i actualMousePosition(mouse_->getPosition(*window_));
    sf::Vector2f mappedMousePosition = window_->mapPixelToCoords(actualMousePosition);
    return mappedMousePosition;
}

