#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
//************************************************
// entitymanager.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"
#include "character.h"
#include "bullet.h"
#include <list>
#include "observer.h"
#include <stack>

class EntityManager: public Observer
{
    public:
        EntityManager(sf::RenderWindow*, sf::Mouse*);
        virtual void on_notify(Event);
        void render(void);
        void new_entity(Entity*);
        void del_entity(int);
        void update_all(void);
    private:
        int id_count;
        void purge(void);
        std::stack<int> purge_list;
        Character* character_;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        std::list<Entity*> entities;
};

#endif

