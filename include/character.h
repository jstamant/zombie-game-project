#ifndef _CHARACTER_H
#define _CHARACTER_H
//************************************************
// character.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "defines.h"
#include "entity.h"
//#include "observer.h"
//#include "subject.h"

//class Character: public Entity, public Observer
class Character: public Entity
{
    public:
        Character();
        Character(int, int);
        //virtual void on_notify(Event);
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
        virtual void update_logic(void);
        virtual bool is_character(void);
    private:
        double angle;
};

#endif

