//************************************************
// entitymanager.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "defines.h"
#include <deque>
#include "enemy.h"
#include "entity.h"
#include "entitymanager.h"
#include <list>
#include <stack>

//DEBUG
#include <iostream>

EntityManager::EntityManager(sf::RenderWindow* window, sf::Mouse* mouse) {
    window_ = window;
    mouse_  = mouse;
    character_ = NULL;
    for (int i=1; i<=MAX_ENTITIES; i++)
        available_ids.push_back(i);
}

void EntityManager::on_notify(Event event, int id) {
    switch (event) {
        case SHOOT:
            if (character_)
                character_->shoot();
            break;
        case MOVE_UP:
            if (character_)
                character_->move_up();
            break;
        case MOVE_DOWN:
            if (character_)
                character_->move_down();
            break;
        case MOVE_LEFT:
            if (character_)
                character_->move_left();
            break;
        case MOVE_RIGHT:
            if (character_)
                character_->move_right();
            break;
        case NEW_BULLET:
            //do something;
            break;
        default:
            break;
    }
}

void EntityManager::render(void) {
    //Render all entities
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        window_->draw(**it);
    }
}

void EntityManager::new_entity(Entity* entity) {
    std::cout << "New ID: " << available_ids.front() << std::endl;
    entity->set_window(window_);
    entity->set_mouse(mouse_);
    entity->set_entitymanager(this);
    entity->set_id(available_ids.front());
    available_ids.pop_front();
    if (entity->is_enemy())
        Enemy::character_ = character_;
    entities.push_back(entity);
    if (entity->is_character())
        character_ = dynamic_cast<Character*>(entity);
}

/* Add an entity to the purge list for later removal.
 * Entities can't be deleted during the update() loop, because the iterator in
 * the update() loop will no longer point to the next entity. Undefined
 * behaviour follows.
 * @param id: ID of the entity for removal
 */
void EntityManager::del_entity(int id) {
    purge_list.push(id);
    available_ids.push_back(id);
}

/* Remove entities slated for removal.
 */
void EntityManager::purge(void) {
    int delete_id = 0;
    while (!purge_list.empty()) {
        delete_id = purge_list.top();
        purge_list.pop();
        for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
            if ( (*it)->get_id() == delete_id ){
                delete *it;
                entities.erase(it);
                break;
            }
        }
    }
}

/* void EntityManager::update_all(void)
 * Updates the logic of all its tracked entities.
 */
void EntityManager::update_all(void) {
    purge();
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        (*it)->update_logic();
    }
}

/* Searches its list of entities for a character entity, and sets its
 * character_ reference to it.
 */
/*
void EntityManager::bind_character(void) {
    //int id = 0;
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        if (((*it)->is_character())) {
            std::cout << "Character found!\n"; //DEBUG
            character_ = dynamic_cast<Character*>(*it);
            //id = (*it)->get_id();
            //std::cout << "ID: " << id << std::endl; //DEBUG
        }
    }
    //character_ = entities;
}
*/

/* Check collisions of a rect with all entities.
 * @param rect: Rectangle to check collisions with all entities
 * @return list: List of all entities that collide with the input rect
 */
std::list<Entity*> EntityManager::check_collisions(sf::FloatRect rect) {
    std::list<Entity*> collision_list;
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        if ((*it)->get_rect().intersects(rect))
            collision_list.push_back(*it);
    }
    return collision_list;
}

