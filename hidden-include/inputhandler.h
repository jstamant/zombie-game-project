#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "defines.h"
#include "entity.h"
#include "subject.h"
#include <vector>

class InputHandler: public Subject
{
    public:
        InputHandler(sf::RenderWindow*);
        void handle_input(void);
    private:
        sf::RenderWindow* window_;
        sf::Mouse mouse;
        sf::Event event;
};

#endif

