#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "command.h"
#include <vector>

class InputHandler
{
    public:
        InputHandler(sf::RenderWindow*);
        std::vector<Command*> handle_input(void);
    private:
        sf::RenderWindow* window;
        sf::Mouse mouse;
        sf::Event event;
        std::vector<Command*> input_queue;
        MouseMovement mouse_movement_command;
        KeyW key_w_command;
        KeyA key_a_command;
        KeyS key_s_command;
        KeyD key_d_command;
        Command* mouse_movement;
        Command* key_w;
        Command* key_a;
        Command* key_s;
        Command* key_d;
};

#endif

