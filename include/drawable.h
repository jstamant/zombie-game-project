#ifndef _ENTITY_H_
#define _ENTITY_H_

//Include SFML dependencies
#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity();
        Entity(int, int);
        sf::Sprite get_sprite(void);
        void set_window(sf::RenderWindow*);
        void set_mouse(sf::Mouse*);
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        int id;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
};

#endif
