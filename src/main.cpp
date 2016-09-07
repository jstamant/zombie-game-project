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
#include "observer.h"
#include <vector>

//DEBUG
#include <iostream>

int main()
{
    //Define core resources
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_CAPTION);
    EntityManager entitymanager(window);
    InputHandler input_handler(&window, &entitymanager);
    std::vector<Command*> command;
    sf::Mouse mouse;

    window.setFramerateLimit(FRAMELIMIT);

    //Create some test entities
    //Character test_character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &window, &mouse);
    //test_character.add_observer(&entitymanager);
    //input_handler.add_observer(&test_character);
    Enemy enemy(&entitymanager);
    Enemy::p_character_ref = &test_character;

    //Run the game
    while (window.isOpen())
    {
        //Process input
        input_handler.handle_input();
        /*
        command.clear(); //Wipe the vector to ensure a clean slate
        command = input_handler.handle_input();
        //Perform actions determined by input
        while (!command.empty()) {
            (command.back())->execute(test_character);
            command.pop_back();
        }
        */

        enemy.seek_player();

        //Render
        window.clear(sf::Color(192, 192, 192));
        //window.draw(test_character.get_sprite());
        window.draw(enemy.get_sprite());
        entitymanager.render();

        window.display();
    }

    return 0;
}

