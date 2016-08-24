#ifndef _BULLET_H
#define _BULLET_H

#include "drawable.h"
#include "character.h"

class Bullet: public Drawable
{
    public:
        Bullet();
        Bullet(Character);
        sf::Sprite get_sprite(void);
        bool is_active(void);
    private:
        static sf::Texture texture;
        sf::Sprite sprite;
        bool active;
};

#endif
