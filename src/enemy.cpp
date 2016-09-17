//************************************************
// enemy.cpp
//************************************************

//Include dependencies
#include "character.h"
#include <cmath>
#include "enemy.h"

//TODO remove this once the global is phased out
extern Character* g_character;

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
    float character_x = g_character->get_x();
    float character_y = g_character->get_y();
    float dx = character_x - x_;
    float dy = character_y - y_;
    float distance = sqrt(pow(dx,2) + pow(dy,2));
    float ratio = Z_SPEED/distance;

    //Calculate x and y movement
    float move_x = ratio*dx;
    float move_y = ratio*dy;

    //Perform movement
    move(move_x, move_y);
    rect_ = sprite_.getGlobalBounds();
}

void Enemy::update_logic(void) {
    seek_player();
}

bool Enemy::is_collidable(void) { return true; }
bool Enemy::is_enemy(void)      { return true; }

