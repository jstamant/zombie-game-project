#ifndef _BULLET_H
#define _BULLET_H
//************************************************
// bullet.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"

class Bullet: public Entity
{
    public:
        Bullet(sf::Vector2f, sf::Vector2f);
        //~Bullet();
        sf::VertexArray get_line(void);
        virtual void update_logic(void);
    private:
        int time_to_live;
        sf::VertexArray line;
};

#endif

