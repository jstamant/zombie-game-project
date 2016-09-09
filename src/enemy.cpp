//************************************************
// enemy.cpp
//************************************************

//Include dependencies
#include "character.h"
#include "enemy.h"
#include <cmath>

Enemy::Enemy() {
    texture.loadFromFile("enemy.png");
    sprite_.setTexture(texture);
    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
}

/* Steps the enemy directly towards the character.
 * TODO This could potentially benefit from vector math.
 */
void Enemy::seek_player(void) {
    float character_x = character_->get_x();
    float character_y = character_->get_y();
    float dx = character_x - sprite_.getPosition().x;
    float dy = character_y - sprite_.getPosition().y;
    float distance = sqrt(pow(dx,2) + pow(dy,2));
    float ratio = Z_SPEED/distance;

    //Calculate x and y movement
    float move_x = ratio*dx;
    float move_y = ratio*dy;

    //Perform movement
    sprite_.move(move_x, move_y);
}

void Enemy::update_logic(void) {
    seek_player();
}

bool Enemy::is_enemy(void) { return true; }

Character* Enemy::character_ = NULL; //Character reference is added later

