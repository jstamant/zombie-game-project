//******************************************************************************
// character.cpp
//******************************************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>

// //Include dependencies
// #include "bullet.h"
#include "character.h"
// #include "defines.h"
// #include "entity.h"
// #include "entitymanager.h"
#include <math.h>

//DEBUG
//#include <iostream>

// //TEMPORARY
// extern sf::View globalView;

Character::Character() {
    sprite.offsetX = 16;
    sprite.offsetY = 16;
//     spriteWidth = 32;
//     spriteHeight = 32;
//     set_sprite();

//     sprite_.setOrigin(16, 16);
//     rect_ = sprite_.getGlobalBounds();
//     ammo_ = 10;
//     m_health = 100;
}

Character::Character(int x, int y): Character::Character() {
    setPosition(x, y);
}

// //******************************************************************************
// // Access functions
// //******************************************************************************

// int   Character::getAmmo(void)     { return ammo_; }
// float Character::get_x(void)       { return sprite_.getPosition().x; }
// float Character::get_y(void)       { return sprite_.getPosition().y; }

// void  Character::setAmmo(int ammo) { ammo_ = ammo; }

//******************************************************************************
// Update functions
//******************************************************************************

/* Rotates the character to face the mouse pointer.
 */
void Character::rotate(void) {
    //SDL_Point mousePosition = findMouseCoords();
    SDL_Point mouse_position;
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    SDL_Point angle_vector;
    angle_vector.x = mouse_position.x - x_;
    angle_vector.y = mouse_position.y - y_;
    angle_ = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
    //sprite_.setRotation(angle_);
}

// /* Generates a bullet, and passes it to the entity manager for tracking.
//  */
// void Character::shoot(void) {
//     sf::Vector2f mousePosition;
//     Bullet* bullet;
//     if (ammo_ > 0)
//     {
//         mousePosition = findMouseCoords();
//         bullet = new Bullet(sprite_.getPosition(), mousePosition);
//         entitymanager_->new_entity(bullet);
//         ammo_--;
//     }
// }

void Character::updateLogic(void)
{
    rotate();
    // if (m_health <= 0) {
    //     kill();
    // }
    // globalView.setCenter(x_, y_);
}

// //******************************************************************************
// // Entity-type checking functions
// //******************************************************************************

// bool Character::is_character(void)  { return true; }
// bool Character::is_collidable(void) { return true; }

// //******************************************************************************
// // General-purpose functions
// //******************************************************************************

// sf::Vector2f Character::findMouseCoords(void) {
//     sf::Vector2i actualMousePosition(mouse_->getPosition(*window_));
//     sf::Vector2f mappedMousePosition = window_->mapPixelToCoords(actualMousePosition);
//     return mappedMousePosition;
// }

