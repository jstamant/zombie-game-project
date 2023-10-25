#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL.h>

// TODO this isn't very efficient. All this data is getting copied for each
// entity, other than the spritesheet.

class Sprite
{
public:
    Sprite();
    static SDL_Texture* spritesheet;
    SDL_Rect rect;
    //TODO turn offset into a struct like SDL point?
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
