//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "character.h"
#include "defines.h"
#include "enemy.h"
#include "entitymanager.h"
#include "inputhandler.h"
#include <vector>

int main()
{
    //Define core resources
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_CAPTION);
    InputHandler input_handler(&window);
    std::vector<Command*> command;
    sf::Mouse mouse;
    EntityManager entitymanager;

    window.setFramerateLimit(FRAMELIMIT);

    //Create some test entities
    Character character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &window, &mouse);
    Enemy enemy(&entitymanager);

    while (window.isOpen())
    {
        //Process input
        //Note: I'm not sure if a std::vector is the best interface for this.
        command.clear(); //Wipe the vector to ensure a clean slate
        command = input_handler.handle_input();
        //Perform actions determined by input
        while (!command.empty()) {
            (command.back())->execute(character);
            command.pop_back();
        }

        enemy.seek_player(&character);

        window.clear(sf::Color(192, 192, 192));
        window.draw(character.get_sprite());
        window.draw(enemy.get_sprite());

        window.display();
    }

    return 0;
}

