//************************************************
// entity.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"
#include "entitymanager.h"
#include "defines.h"
#include <iostream>
#include <math.h>

//Initialize static members
sf::Texture* Entity::spritesheet_ = NULL;

Entity::Entity(): Entity::Entity(0, 0) {
    x_ = 0;
    y_ = 0;
    sf::FloatRect rect_(0, 0, 0, 0);
    origin_x_ = 16;
    origin_y_ = 16;
    m_health = 1;
    if ( spritesheet_ == NULL ) {
        sf::Image image;
        if(!image.loadFromFile("spritesheet.png"))
            std::cout << "Failed to load image." << std::endl;
        image.createMaskFromColor(sf::Color::Magenta);
        spritesheet_ = new sf::Texture;
        if(!spritesheet_->loadFromImage(image))
            std::cout << "Failed to load texture from image." << std::endl;
    }
    sprite_.setTexture(*spritesheet_);
    mouse_ = NULL;
    window_ = NULL;
    entitymanager_ = NULL;
}

Entity::Entity(int x, int y) {
    set_position(x, y);
}

/* Moves the entity relative to its current position.
 * @param x Relative movement to incur in the x-axis.
 * @param y Relative movement to incur in the y-axis.
 */
void Entity::move(float x, float y) {
    set_position(x_ + x, y_ + y);
}

//************************************************
// Access functions
//************************************************

int            Entity::get_health(void)   { return m_health; }
int            Entity::get_id(void)       { return id_; }
sf::Vector2f   Entity::get_position(void) { return sf::Vector2f(x_, y_); }
sf::FloatRect* Entity::get_rect(void)     { return &rect_; }
sf::Sprite     Entity::get_sprite(void)   { return sprite_; }


void Entity::setCollisionList(std::list<ID> list) { collisionList_ = list; }
void Entity::set_id(int id) { id_ = id; }

void Entity::set_entitymanager(EntityManager* entitymanager) { entitymanager_ = entitymanager; }


void Entity::set_mouse(sf::Mouse* mouse) {
    mouse_ = mouse;
}

/* Set the absolute position of the entity.
 */
void Entity::set_position(float x, float y) {
    x_ = x;
    y_ = y;
    sprite_.setPosition(x, y);
    rect_.left = x - origin_x_;
    rect_.top  = y - origin_y_;
}


//************************************************
// Entity-type checking functions (deprecated?)
//************************************************

bool Entity::is_bullet(void)     { return false; }
bool Entity::is_character(void)  { return false; }
bool Entity::is_collidable(void) { return false; }
bool Entity::is_enemy(void)      { return false; }
bool Entity::is_pickup(void)     { return false; }
bool Entity::is_solid(void)      { return false; }


/* Provide a default draw function for all entities that can be overriden by
 * derived classes. By default, render the entity's sprite.
 */
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

/* Set's the sprite's sub-texture rect on the spritesheet.
 * Added by Joel
 * TODO rename to initialize_sprite
 */
void Entity::set_sprite(){
    sf::Image image;
    if(!image.loadFromFile("spritesheet.png"))
        std::cout << "Failed to load image." << std::endl;
    image.createMaskFromColor(sf::Color::Magenta);
    if(!texture_.loadFromImage(image))
        std::cout << "Failed to load texture from image." << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(spriteOriginX, spriteOriginY, spriteWidth, spriteHeight));
    sprite_.setScale(SCALE, SCALE);
}

void Entity::set_window(sf::RenderWindow* window) {
    window_ = window;
}

//******************************************************************************
// Update functions
//******************************************************************************

void Entity::take_damage(int damage) {
    m_health -= damage;
}

void Entity::kill(void) {
    entitymanager_->del_entity(id_);
}

