//NO HEADER GUARD NEEDED???

//Include dependencies
#include <SFML/Graphics.hpp>
#include "character.h"
#include "defines.h"
#include <math.h>

Character::Character() {
    init();
}

Character::Character(int x, int y) {
    init();
    set_pos(x, y);
}

void Character::init(void) {
    sprite.setPosition(0, 0);
    for (int dir=0; dir<MOVEMENT_KEYS; dir++)
        movement[dir] = 0;
    texture.loadFromFile("character.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
}

void Character::set_pos(int x, int y) {
    sprite.setPosition(x, y);
}

void Character::move(void) {
    int x = movement[MOVEMENT_RIGHT] - movement[MOVEMENT_LEFT];
    int y = movement[MOVEMENT_DOWN] - movement[MOVEMENT_UP];
    sprite.move(x, y);
}

//Rotates the character to face the mouse pointer.
void Character::rotate(sf::RenderWindow* window, sf::Mouse* mouse) {
    sf::Vector2i angle_vector(mouse->getPosition(*window) - (sf::Vector2i)sprite.getPosition());
    double angle = atan2(angle_vector.y, angle_vector.x) * 180 / PI;
    sprite.setRotation(angle);
}

sf::Sprite Character::get_sprite(void) {
    return sprite;
}

void Character::set_movement(int direction, int speed) {
    movement[direction] = speed;
}

