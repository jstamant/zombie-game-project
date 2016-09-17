//************************************************
// drawable.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"
//#include "entitymanager.h"

Entity::Entity() : Entity::Entity(0, 0) {
    x_ = 0;
    y_ = 0;
    sf::FloatRect rect_(0, 0, 0, 0);
    mouse_  = NULL;
    window_ = NULL;
    entitymanager_ = NULL;
}

Entity::Entity(int x, int y) {
    sprite_.setPosition(x, y);
}

sf::Sprite Entity::get_sprite(void) {
    return sprite_;
}

void Entity::set_window(sf::RenderWindow* window) {
    window_ = window;
}

void Entity::set_mouse(sf::Mouse* mouse) {
    mouse_ = mouse;
}

void Entity::set_entitymanager(EntityManager* entitymanager) {
    entitymanager_ = entitymanager;
}

void Entity::set_id(int id) { id_ = id; }

int Entity::get_id(void) { return id_; }

sf::FloatRect Entity::get_rect(void) { return rect_; }

bool Entity::is_bullet(void)     { return false; }
bool Entity::is_character(void)  { return false; }
bool Entity::is_collidable(void) { return false; }
bool Entity::is_enemy(void)      { return false; }

/* Provide a default draw function for all entities that can be overriden by
 * derived classes. By default, render the entity's sprite.
 */
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

