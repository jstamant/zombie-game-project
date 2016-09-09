#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "command.h"
#include "defines.h"
#include "entity.h"
//#include "observer.h"
#include "subject.h"
#include <vector>

//class InputHandler: public Subject, public Observer
class InputHandler: public Subject
{
    public:
        InputHandler(sf::RenderWindow*);
        void handle_input(void);
    private:
        //virtual void on_notify(Event, int=0);
        sf::RenderWindow* window_;
        sf::Mouse mouse;
        sf::Event event;
        std::vector<Command*> input_queue;
        /*
        KeyW key_w_command;
        KeyA key_a_command;
        KeyS key_s_command;
        KeyD key_d_command;
        Command* key_w;
        Command* key_a;
        Command* key_s;
        Command* key_d;
        */
};

#endif

