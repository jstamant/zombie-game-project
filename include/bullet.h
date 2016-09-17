#ifndef _BULLET_H
#define _BULLET_H
//************************************************
// bullet.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"
#include <list>

class Bullet: public Entity
{
    public:
        Bullet(sf::Vector2f, sf::Vector2f);
        //~Bullet();
        sf::VertexArray get_line(void);
        virtual void update_logic(void);
        virtual bool is_bullet(void);
    private:
        int time_to_live;
        float slope_;
        sf::VertexArray line;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
        bool checked_collisions;
        void find_potential_collisions(void);
        void find_first_collision(void);
        std::list<Entity*> collision_list;
        void extend_line(void);
};

#endif

