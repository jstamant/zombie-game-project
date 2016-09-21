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
#include <list>

class Character: public Entity
{
    public:
        Character();
        Character(int, int);
        float get_x(void);     //DEPRECATED
        float get_y(void);     //DEPRECATED
        double get_angle(void);//DEPRECATED
        void rotate(void);
        void shoot(void);
        virtual void update_logic(void);
        virtual bool is_character(void);
        virtual bool is_collidable(void);
        int  getAmmo(void);
        void setAmmo(int);
    private:
        //double angle;
        int ammo_;
        sf::FloatRect m_intersect_rect;
        std::list<Entity*> m_collision_list;
};

#endif

