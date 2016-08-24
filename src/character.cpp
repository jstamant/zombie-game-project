//Include dependencies
#include "character.h"
#include "defines.h"
#include "drawable.h"
#include <math.h>
#include <SFML/Graphics.hpp>

Character::Character() {
    texture.loadFromFile("character.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16, 16);
}

Character::Character(int initial_x, int initial_y,
                     sf::RenderWindow* reference_window,
                     sf::Mouse* reference_mouse) : Character::Character() {
    set_pos(initial_x, initial_y);
    window_access = reference_window;
    mouse_access = reference_mouse;
}

void Character::set_pos(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    sprite.setPosition(x, y);
}

int Character::get_x(void) {
    return x;
}

int Character::get_y(void) {
    return y;
}

double Character::get_angle(void) {
    return angle;
}

void Character::move_up(void) {
    y -= SPEED;
    set_pos(x, y);
}

void Character::move_down(void) {
    y += SPEED;
    set_pos(x, y);
}

void Character::move_left(void) {
    x -= SPEED;
    set_pos(x, y);
}

void Character::move_right(void) {
    x += SPEED;
    set_pos(x, y);
}

//Rotates the character to face the mouse pointer.
void Character::rotate(void) {
    sf::Vector2i mouse_vector(mouse_access->getPosition(*window_access));
    sf::Vector2i sprite_vector(sprite.getPosition());
    sf::Vector2i angle_vector(mouse_vector - sprite_vector);
    angle = atan2(angle_vector.y, angle_vector.x) * 180 / PI;
    sprite.setRotation(angle);
}

void Character::shoot(void) {
    //Generate a muzzle flash
    //Game logic to hit things
}

sf::Sprite Character::get_sprite(void) {
    return sprite;
}

