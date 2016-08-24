#include "bullet.h"
#include "character.h"

//Declare static members;
sf::Texture Bullet::texture; 

//Bullet::Bullet() : Bullet::Bullet(Character) {}
Bullet::Bullet() {
    //TODO fix where initialisation of this static variable goes.
    texture.loadFromFile("bullet.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
    active = false;
}

Bullet::Bullet(Character character) : Bullet::Bullet() {
    sprite.setPosition(character.get_x(), character.get_y());
    sprite.setRotation(character.get_angle());
    //Will this override active from the initializer list?
    active = true;
}

sf::Sprite Bullet::get_sprite(void) {
    return sprite;
}

bool Bullet::is_active(void) {
    return active;
}

