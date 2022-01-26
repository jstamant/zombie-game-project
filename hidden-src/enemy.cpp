//************************************************
// enemy.cpp
//************************************************

//Include dependencies
#include "character.h"
#include "enemy.h"
#include "globals.h"
// #include "entity.h"
// #include "entitymanager.h"
#include <math.h>

// //DEBUG
// #include <iostream>

extern Character gCharacter;

Enemy::Enemy() {
    target_ = NULL;
    sprite.offsetX = 16;
    sprite.offsetY = 16;
    sprite.setRow(1);
    //sprite_.setOrigin(16, 16);
    //rect_ = sprite_.getGlobalBounds();
    //m_health = 100;
}

Enemy::Enemy(int x, int y): Enemy::Enemy() {
    setPosition(x, y);
}

//******************************************************************************
// Access functions
//******************************************************************************

void Enemy::setTarget(Character* character) {
    target_ = character;
}

//******************************************************************************
// Update functions
//******************************************************************************

/* Steps the enemy directly towards the character.
 */
void Enemy::seekPlayer(void) {
    if (target_ != NULL) {
        SDL_FPoint character_position = target_->getPosition();
        float dx = character_position.x - x_;
        float dy = character_position.y - y_;
        double raw_angle = atan2(dy, dx);
        float move_x = Z_SPEED*cos(raw_angle);
        float move_y = Z_SPEED*sin(raw_angle);
        angle_ = raw_angle*180/M_PI;
        //Perform movement
        move(move_x, move_y);
    }
}

void Enemy::updateLogic(void) {
    //seekPlayer(&gCharacter);
    move(-Z_SPEED, 0);
    //if (m_health <= 0)
    //    kill();
}

// bool Enemy::is_collidable(void) { return true; }
// bool Enemy::is_enemy(void)      { return true; }
