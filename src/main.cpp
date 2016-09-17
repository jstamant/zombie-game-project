//************************************************
// main.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "character.h"
#include "defines.h"
#include "enemy.h"
#include "entitymanager.h"
#include "inputhandler.h"
#include "pickup.h"
#include "userinterface.h"

//Make this character reference global for now... :/
Character* g_character = NULL;

int main()
{
    //Define core resources
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_CAPTION);
    sf::Mouse mouse;

    EntityManager entitymanager(&window, &mouse);
    InputHandler input_handler(&window);
    input_handler.add_observer(&entitymanager);

    window.setFramerateLimit(FRAMELIMIT);

    //Create some test entities
    entitymanager.new_entity(new Character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
    entitymanager.new_entity(new Enemy);
    entitymanager.new_entity(new UserInterface);
    entitymanager.new_entity(new Pickup(100, 100));
    long unsigned int enemy_spawn = 0;
    long unsigned int pickup_spawn = 0;

    //Run the game
    while (window.isOpen())
    {
        //Process input
        input_handler.handle_input();

        //Perform game logic
        entitymanager.update_all();
        //DEBUG
        if (enemy_spawn++ >= 100) {
            entitymanager.new_entity(new Enemy);
            enemy_spawn = 0;
        }
        if (pickup_spawn++ >= 700) {
            entitymanager.new_entity(new Pickup(300,300));
            pickup_spawn = 0;
        }

        //Render
        window.clear(sf::Color(192, 192, 192));
        entitymanager.render();

        window.display();
    }

    return 0;
}

