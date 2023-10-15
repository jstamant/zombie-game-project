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
    Bullet(SDL_Point, SDL_Point);
    void draw(SDL_Renderer *);
    int ttl;
private:
    SDL_Point source;
    SDL_Point target;
    void extendLine(void);
};

#endif //_BULLET_H_
