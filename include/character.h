#ifndef _CHARACTER_H
#define _CHARACTER_H

//Include dependencies
#include "drawable.h"
#include <SFML/Graphics.hpp>

class Character: public Drawable
{
    public:
        Character();
        Character(int, int, sf::RenderWindow*, sf::Mouse*);
        void set_pos(int, int);
        float get_x(void);
        float get_y(void);
        double get_angle(void);
        void move_up(void);
        void move_down(void);
        void move_left(void);
        void move_right(void);
        void rotate(void);
        void shoot(void);
        sf::Sprite get_sprite(void);
    private:
        int x, y;
        double angle;
        sf::RenderWindow* window_access;
        sf::Mouse* mouse_access;
};

#endif
