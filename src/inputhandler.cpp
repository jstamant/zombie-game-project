//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "inputhandler.h"
#include <vector>

InputHandler::InputHandler(sf::RenderWindow* source_window) {
    window = source_window;
    mouse_movement = &mouse_movement_command;
    key_w = &key_w_command;
    key_a = &key_a_command;
    key_s = &key_s_command;
    key_d = &key_d_command;
}

//Processes the different sources of input, appends any valid input into
//a queue, and returns the queue.
std::vector<Command*> InputHandler::handle_input(void) {
    //Clear the input queue. This assumes all previous input has been handled.
    input_queue.clear();
    //First, process the SFML event queue
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            //TODO move this command out of this class
            window->close();
        if (event.type == sf::Event::MouseMoved) {
            input_queue.push_back(mouse_movement);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                //Perform character shooting
                //character.shoot();
                /*//OLD Perform character shooting
                if (bullet_counter < MAX_BULLETS) {
                    *p_bullet++ = Bullet(character);
                    bullet_counter++;
                }else{
                    p_bullet = bullets;
                    *p_bullet++ = Bullet(character);
                    bullet_counter = 0;
                }*/
            }
        }
    }
    //Second, process the movement keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        input_queue.push_back(key_w);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        input_queue.push_back(key_a);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        input_queue.push_back(key_s);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        input_queue.push_back(key_d);
    return input_queue;
}
