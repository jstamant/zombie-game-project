#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// bullet.h
//******************************************************************************

//Include dependencies
#include <SDL2/SDL.h>

class Bullet
{
public:
    Bullet(SDL_Point);
    SDL_Point target;
    int ttl;
};

#endif //_BULLET_H_
