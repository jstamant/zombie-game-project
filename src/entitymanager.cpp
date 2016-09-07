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

EntityManager::EntityManager(sf::RenderWindow& source_window) {
    window = &source_window;
    //Character character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &window, &mouse);
    //character.add_observer((Observer*)this?);
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
    std::cout << "Rendering: "; //DEBUG
    //Render all characters
    //window->draw(character.get_sprite());
    //Render all enemies
    //Render all bullets
    for (std::list<Bullet>::iterator it=bullet_list.begin(); it!=bullet_list.end(); it++) {
        window->draw(it->get_line());
        std::cout << "OMG BULLET\n"; //DEBUG
    }
    std::cout << "Done!\n"; //DEBUG
}

