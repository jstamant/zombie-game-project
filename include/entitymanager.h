#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "drawable.h"
#include <list>
#include "observer.h"
#include <vector>

class EntityManager : public Observer
{
    public:
        EntityManager(sf::RenderWindow*, sf::Mouse*);
        void on_notify(Event);
        void render(void);
        void new_entity(Entity*);
    private:
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        Character character;
        std::list<Bullet> bullet_list;
        std::list<Entity*> entities;
};

#endif

