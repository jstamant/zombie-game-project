//enemy.cpp

//Include dependencies
#include "character.h"
#include "enemy.h"
#include "observer.h"

Enemy::Enemy(Observer* observer) {
    texture.loadFromFile("enemy.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
    add_observer(observer);
}

void Enemy::seek_player(Character* character) {
    int x = (int)((character->get_sprite()).getPosition()).x;
    int y = (int)((character->get_sprite()).getPosition()).y;
    int dx = x - (int)(sprite.getPosition()).x;
    int dy = y - (int)(sprite.getPosition()).y;

    //Perform movement
    if (dx > 0) sprite.move(1, 0);
    if (dx < 0) sprite.move(-1, 0);
    if (dy > 0) sprite.move(0, 1);
    if (dy < 0) sprite.move(0, -1);
}

