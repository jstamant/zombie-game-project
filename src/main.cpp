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
    //Character test_character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &window, &mouse);
    //test_character.add_observer(&entitymanager);
    //input_handler.add_observer(&test_character);
    //Enemy enemy(&entitymanager);
    //Enemy::p_character_ref = &test_character;
    entitymanager.new_entity(new Character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
    //entitymanager.new_entity(new Enemy);

    //Run the game
    while (window.isOpen())
    {
        //Process input
        input_handler.handle_input();

        //Perform game logic
        //enemy.seek_player();

        //Render
        window.clear(sf::Color(192, 192, 192));
        //window.draw(enemy.get_sprite());
        entitymanager.render();

        window.display();
    }

    return 0;
}

