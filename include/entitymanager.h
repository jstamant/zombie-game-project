#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
//************************************************
// entitymanager.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include <deque>
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
        virtual void on_notify(Event, int);
        void render(void);
        void new_entity(Entity*);
        void del_entity(int);
        sf::Vector2f pop_collision_point(void);
        void update_all(void);
        std::list<Entity*> check_collisions(sf::FloatRect);
        std::list<Entity*> collision_line(sf::Vector2f, sf::Vector2f);
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
};

#endif

