#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
//************************************************
// entitymanager.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include std dependencies
#include <deque>
#include <list>
#include <stack>

//Include dependencies
#include "defines.h"
#include "entity.h"
#include "character.h"
#include "bullet.h"
#include "observer.h"
#include "system.h"

class EntityManager: public System, public Observer, public Subject
{
    public:
        EntityManager(sf::RenderWindow*, sf::Mouse*);
        //Access functions
        void getEntityByID(ID);
        //Communication functions
        virtual void onNotify(Event, Entity*);
        void render(void);
        void new_entity(Entity*);
        void new_tile(Entity*);
        void del_entity(int);
        sf::Vector2f pop_collision_point(void);
        void update_all(void);
        std::list<Entity*> check_collisions(sf::FloatRect);
        //std::list<Entity*> check_collisions_pickups(sf::FloatRect);
        //std::list<Entity*> collision_line(sf::Vector2f, sf::Vector2f);
    private:
        void purge(void);
        std::stack<int> purge_list;
        std::deque<int> available_ids;
        Character* character_;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        sf::Vector2f m_collision_point;
        std::list<Entity*> entities;
        std::list<Entity*> collidables;
        std::list<Entity*> pickups;
        std::list<Entity*> tiles;
};

#endif

