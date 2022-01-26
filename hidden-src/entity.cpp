//************************************************
// entity.cpp
//************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "entity.h"
// #include "entitymanager.h"
#include "globals.h"
// #include <iostream>
// #include <math.h>

Entity::Entity(): Entity::Entity(0, 0) {
    x_ = 0;
    y_ = 0;
}

Entity::Entity(int x, int y) {
    setPosition(x, y);
}

/* Moves the entity relative to its current position.
 * @param x Relative movement to incur in the x-axis.
 * @param y Relative movement to incur in the y-axis.
 */
void Entity::move(float dx, float dy) {
    setPosition(x_ + dx, y_ + dy);
}

//************************************************
// Access functions
//************************************************

// int            Entity::get_health(void)   { return m_health; }
int        Entity::getID(void)       { return id_; }
SDL_FPoint Entity::getPosition(void) {
    SDL_FPoint position;
    position.x = x_;
    position.y = y_;
    return position;
}

// void Entity::setCollisionList(std::list<ID> list) { collisionList_ = list; }
void Entity::setID(int id) { id_ = id; }

// void Entity::set_entitymanager(EntityManager* entitymanager) { entitymanager_ = entitymanager; }


// void Entity::set_mouse(sf::Mouse* mouse) {
//     mouse_ = mouse;
// }

/* Set the absolute position of the entity.
 */
void Entity::setPosition(float x, float y) {
    x_ = x;
    y_ = y;
}


// //************************************************
// // Entity-type checking functions (deprecated?)
// //************************************************

// bool Entity::is_bullet(void)     { return false; }
// bool Entity::is_character(void)  { return false; }
// bool Entity::is_collidable(void) { return false; }
// bool Entity::is_enemy(void)      { return false; }
// bool Entity::is_pickup(void)     { return false; }
// bool Entity::is_solid(void)      { return false; }


// /* Provide a default draw function for all entities that can be overriden by
//  * derived classes. By default, render the entity's sprite.
//  */
// void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     target.draw(sprite_, states);
// }

// void Entity::set_window(sf::RenderWindow* window) {
//     window_ = window;
// }

// /* Provide a default draw function for all entities that can be overriden by
//  * derived classes. By default, render the entity's sprite.
//  */
/* Method for rendering the object at coordinates x,y
 */
void Entity::draw(void) const {
    SDL_Rect dest;
    dest.x = x_-sprite.offsetX;
    dest.y = y_-sprite.offsetY;
    dest.w = sprite.rect.w;
    dest.h = sprite.rect.h;
    //SDL_RenderCopy(gRenderer, sprite.spritesheet, &(sprite.rect), &dest);
    //Render entity's sprite to screen, with rotation around the sprite's center
    SDL_RenderCopyEx(gRenderer, sprite.spritesheet, &(sprite.rect), &dest, angle_, NULL, SDL_FLIP_NONE);
}

// //******************************************************************************
// // Update functions
// //******************************************************************************

// void Entity::take_damage(int damage) {
//     m_health -= damage;
// }

// void Entity::kill(void) {
//     entitymanager_->del_entity(id_);
// }

