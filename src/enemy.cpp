//enemy.cpp

#include "enemy.h"
#include "character.h"

Enemy::Enemy() {
    texture.loadFromFile("enemy.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
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

