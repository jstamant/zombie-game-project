#ifndef _CHARACTER_H
#define _CHARACTER_H
//************************************************
// character.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "defines.h"
#include "drawable.h"
#include "observer.h"
#include "subject.h"

class Character: public Drawable, public Observer, public Subject
{
    public:
        Character();
        Character(int, int);
        void on_notify(Event);
        void set_pos(int, int);
        float get_x(void);
        float get_y(void);
        double get_angle(void);
        void move_up(void);
        void move_down(void);
        void move_left(void);
        void move_right(void);
        void rotate(void);
        sf::Sprite get_drawable(void);
    private:
        int x, y;
        double angle;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
};

#endif
