//******************************************************************************
// sprite.cpp
//******************************************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "functions.h"
#include <iostream>
#include "sprite.h"

//Define static members. Required, as they are 'incomplete types' until defined.
SDL_Texture* Sprite::spritesheet = NULL;

Sprite::Sprite() {
    //Centered for a 32x32 pixel sprite by default
    offsetX = 16;
    offsetY = 16;
    //Default sprite is the player sprite
    row_ = 0;
    frame_ = 1;
    //Default clip is a 32x32 pixel sprite
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;
    //Load spritesheet if not already done
    if (spritesheet == NULL) {
        spritesheet = loadTexture("spritesheet.png");
        std::cout << "Loaded spritesheet for an entity" << std::endl;
        if (spritesheet == NULL) //Not sure if this works as intended
            std::cout << "Failed to load spritesheet" << std::endl;
    }
    //NEED TO FREE THIS TEXTURE ON DESTRUCTION
}

//******************************************************************************
// Access functions
//******************************************************************************

void Sprite::setRow(int new_row) {
    row_ = new_row;
    rect.y = row_*32;
}

// //******************************************************************************
// // Update functions
// //******************************************************************************

// /* Rotates the character to face the mouse pointer.
//  * TODO use the entity's members for calculations. No need to refer to the
//  * sprite.
//  */
// void Character::rotate(void) {
//     sf::Vector2f mousePosition = findMouseCoords();
//     sf::Vector2f position = get_position();
//     sf::Vector2f angle_vector(mousePosition- position);
//     angle_ = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
//     sprite_.setRotation(angle_);
// }

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

// void Character::update_logic(void)
// {
//     if (mouse_ && window_) {
//         rotate();
//     }
//     if (m_health <= 0) {
//         kill();
//     }
//     globalView.setCenter(x_, y_);
// }

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

