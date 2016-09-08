#ifndef _ENTITY_H_
#define _ENTITY_H_

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entitymanager.h"

class Entity
{
    public:
        Entity();
        Entity(int, int);
        sf::Sprite get_sprite(void);
        void set_window(sf::RenderWindow*);
        void set_mouse(sf::Mouse*);
        void set_entitymanager(EntityManager*);
        void set_id(int);
        int  get_id(void);
        virtual bool is_character(void);
        virtual void update_logic(void) = 0;
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        int x_;
        int y_;
        int id_;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        EntityManager* entitymanager_;
};

#endif
