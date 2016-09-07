//enemy.cpp

//Include dependencies
#include "character.h"
#include "enemy.h"
#include <cmath>
#include "observer.h"

Enemy::Enemy(Observer* observer) {
    texture.loadFromFile("enemy.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
    add_observer(observer);
}

/* void seek_player(void)
 * Steps the enemy directly towards the character.
 * TODO This could potentially benefit from vector math.
 */
void Enemy::seek_player(void) {
    float character_x = p_character_ref->get_x();
    float character_y = p_character_ref->get_y();
    float dx = character_x - sprite.getPosition().x;
    float dy = character_y - sprite.getPosition().y;
    float distance = sqrt(pow(dx,2) + pow(dy,2));
    float ratio = Z_SPEED/distance;

    //Calculate x and y movement
    float move_x = ratio*dx;
    float move_y = ratio*dy;

    //Perform movement
    sprite.move(move_x, move_y);
}

Character* Enemy::p_character_ref = NULL; //Character reference is added later

