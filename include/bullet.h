#ifndef _BULLET_H
#define _BULLET_H
//************************************************
// bullet.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "drawable.h"

class Bullet
{
    public:
        Bullet(sf::Vector2f, sf::Vector2f);
        //~Bullet();
        sf::VertexArray get_line(void);
    private:
        int time_to_live;
        sf::VertexArray line;
};

#endif

