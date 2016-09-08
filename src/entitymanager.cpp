//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "defines.h"
#include "entity.h"
#include "entitymanager.h"
#include <list>
#include <vector>

//DEBUG
#include <iostream>

EntityManager::EntityManager(sf::RenderWindow* window, sf::Mouse* mouse) {
    window_ = window;
    mouse_  = mouse;
    character_ = NULL;
    id_count = 1;
}

void EntityManager::on_notify(Event event) {
    std::cout << "EntityManager notified...\n"; //DEBUG
    switch (event) {
        case SHOOT:
            std::cout << "New bullet!\n"; //DEBUG
            if (character_)
                character_->shoot();
            std::cout << "Done!\n"; //DEBUG
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
        default:
            break;
    }
    std::cout << "EntityManager notify done!\n"; //DEBUG
}

void EntityManager::render(void) {
    std::cout << "Rendering:\n"; //DEBUG
    //Render all entities
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        window_->draw((*it)->get_sprite());
        std::cout << "Character!\n"; //DEBUG
    }
    //window->draw(character.get_sprite());
    //Render all enemies
    //Render all bullets
    /*
    for (std::list<Bullet>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++) {
        window_->draw(it->get_line());
        std::cout << "OMG BULLET\n"; //DEBUG
    }
    std::cout << "Done!\n"; //DEBUG
    */
}

void EntityManager::new_entity(Entity* entity) {
    entity->set_window(window_);
    entity->set_mouse(mouse_);
    entity->set_entitymanager(this);
    entity->set_id(id_count++);
    entities.push_back(entity);
    if (entity->is_character())
        character_ = dynamic_cast<Character*>(entity);
}

/* void EntityManager::update_all(void)
 * Updates the logic of all its tracked entities.
 */
void EntityManager::update_all(void) {
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

