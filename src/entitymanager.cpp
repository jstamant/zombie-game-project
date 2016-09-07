//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "defines.h"
#include "entitymanager.h"
#include <list>
#include <vector>

//DEBUG
#include <iostream>

EntityManager::EntityManager(sf::RenderWindow* window, sf::Mouse* mouse) {
    window_ = window;
    mouse_  = mouse;
}

void EntityManager::on_notify(Event event) {
    std::cout << "EntityManager notified...\n"; //DEBUG
    Bullet bullet(sf::Vector2f(100,200), sf::Vector2f(0,0));
    switch (event) {
        case SHOOT:
            std::cout << "New bullet!\n"; //DEBUG
            bullet_list.push_back(bullet);
            std::cout << "Done!\n"; //DEBUG
            break;
        case MOVE_DOWN:
            std::cout << "Moving down...\n"; //DEBUG
            character.move_right();
            std::cout << "Done!\n"; //DEBUG
        default:
            break;
    }
    std::cout << "EntityManager notify done!\n"; //DEBUG
}

void EntityManager::render(void) {
    std::cout << "Rendering:\n"; //DEBUG
    //Render all characters
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        window_->draw((*it)->get_sprite());
        std::cout << "Character!\n"; //DEBUG
    }
    //window->draw(character.get_sprite());
    //Render all enemies
    //Render all bullets
    for (std::list<Bullet>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++) {
        window_->draw(it->get_line());
        std::cout << "OMG BULLET\n"; //DEBUG
    }
    std::cout << "Done!\n"; //DEBUG
}

void EntityManager::new_entity(Entity* entity) {
    entity->set_window(window_);
    entity->set_mouse(mouse_);
    entities.push_back(entity);
}

