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
        EntityManager(sf::RenderWindow&);
        void on_notify(Event);
        //void generate_bullet(void);
        void render(void);
    private:
        sf::RenderWindow* window;
        Character character;
        std::list<Bullet> bullet_list;
        std::list<Drawable*> drawables;
};

#endif

