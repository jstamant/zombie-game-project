//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include classes
#include "character.h"

//Include dependencies
#include "defines.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Zombie action-survival game");
    sf::Mouse mouse;
    window.setFramerateLimit(60);
    Character character;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                //Perform character movement
                switch (event.key.code)
                {
                    case sf::Keyboard::W:
                        character.set_movement(MOVEMENT_UP);
                        break;
                    case sf::Keyboard::A:
                        character.set_movement(MOVEMENT_LEFT);
                        break;
                    case sf::Keyboard::S:
                        character.set_movement(MOVEMENT_DOWN);
                        break;
                    case sf::Keyboard::D:
                        character.set_movement(MOVEMENT_RIGHT);
                        break;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                //Stop character movement on key release
                switch (event.key.code)
                {
                    case sf::Keyboard::W:
                        character.set_movement(MOVEMENT_UP, 0);
                        break;
                    case sf::Keyboard::A:
                        character.set_movement(MOVEMENT_LEFT, 0);
                        break;
                    case sf::Keyboard::S:
                        character.set_movement(MOVEMENT_DOWN, 0);
                        break;
                    case sf::Keyboard::D:
                        character.set_movement(MOVEMENT_RIGHT, 0);
                        break;
                }
            }
        }
        //Set character position and rotation
        character.move();
        character.rotate(&window, &mouse);

        window.clear(sf::Color::White);
        window.draw(character.get_sprite());
        window.display();
    }

    return 0;
}

