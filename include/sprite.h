#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL.h>

class Sprite
{
public:
    Sprite();
    static SDL_Texture* spritesheet;
    SDL_Rect rect;
    int offsetX;
    int offsetY;
    //Access functions
    void setRow(int);
    void setFrame(int);
private:
    int row_;
    int frame_;
};

#endif //_SPRITE_H_
