//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "defines.h"
#include "inputhandler.h"
#include "subject.h"
#include "observer.h"
#include <vector>

//DEBUG
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow* window, Observer* entitymanager) {
    window_ = window;
    //entitymanager_ = entitymanager;
    add_observer(entitymanager);

    mouse_movement = &mouse_movement_command;
    key_w = &key_w_command;
    key_a = &key_a_command;
    key_s = &key_s_command;
    key_d = &key_d_command;
}

//Processes the different sources of input, appends any valid input into
//a queue, and DOES WHAT WITH IT?
//std::vector<Command*> InputHandler::handle_input(void) {
void InputHandler::handle_input(void) {
    //Clear the input queue. This assumes all previous input has been handled.
    input_queue.clear();
    //First, process the SFML event queue
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window_->close();
        }
        if (event.type == sf::Event::MouseMoved) {
            input_queue.push_back(mouse_movement);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                //Perform character shooting
                std::cout << "Pow!\n"; //DEBUG
                notify(SHOOT);
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
        //input_queue.push_back(key_d);
        notify(MOVE_RIGHT);

    //Finally, issue the commands
    /*while (!input_queue.empty()) {
        (input_queue.back())->execute(test_character);
        input_queue.pop_back();
    }*/
}

void InputHandler::on_notify(Event event) {
    switch (event) {
        case SHOOT:
            ;
            //do something
            break;
    }
}

