#ifndef _DRAWABLE_H
#define _DRAWABLE_H

//Include SFML dependencies
#include <SFML/Graphics.hpp>

class Drawable
{
    public:
        Drawable();
        Drawable(int, int);
        sf::Sprite get_sprite(void);
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif
