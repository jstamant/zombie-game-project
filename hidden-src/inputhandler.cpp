//************************************************
// inputhandler.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "defines.h"
#include "entity.h"
#include "inputhandler.h"
#include "subject.h"
#include "observer.h"
#include <vector>

//DEBUG
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow* window) {
    window_ = window;
}

/* Needs documentation...
 */
void InputHandler::handle_input(void) {
    //First, process the SFML event queue
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window_->close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                //Perform character shooting
                notify(SHOOT, NULL);
            }
        }
    }
    //Then, process the movement keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        notify(MOVE_UP, NULL);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        notify(MOVE_LEFT, NULL);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        notify(MOVE_DOWN, NULL);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        notify(MOVE_RIGHT, NULL);
}

