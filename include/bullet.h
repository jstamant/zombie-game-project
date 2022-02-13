#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// bullet.h
//******************************************************************************

//Include dependencies
#include <SDL2/SDL.h>

// class Bullet: public Entity
class Bullet
{
public:
    SDL_Point source;
    SDL_Point target;
    int ttl;
    double angle;
    void draw(SDL_Renderer*);
};

#endif //_BULLET_H_
