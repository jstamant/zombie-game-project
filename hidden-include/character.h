#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//************************************************
// character.h
//************************************************

//Include SFML dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "defines.h"
#include "entity.h"

class Character: public Entity
{
public:
    Character();
    Character(int, int);
    // //Access functions
    // int    getAmmo(void);
    // float  get_x(void);     //DEPRECATED
    // float  get_y(void);     //DEPRECATED
    // void   setAmmo(int);
    //Update functions
    void rotate(void);
    // void shoot(void);
    void updateLogic(void);
    // //Entity-type checking functions
    // virtual bool is_character(void);
    // virtual bool is_collidable(void);
    // //General-purpose functions
    // sf::Vector2f findMouseCoords(void);
private:
    // //double angle;
    // int ammo_;
};

#endif //_CHARACTER_H_
