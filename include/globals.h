#ifndef _GLOBALS_H_
#define _GLOBALS_H_

//Include dependencies for forward declaring these global variables
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Forward declerations of global variables for use in functions of other files
extern Game gGame;
extern SDL_Event gEventQueue;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;
extern SDL_Texture* gTextTexture;
extern SDL_Window* gWindow;
extern TTF_Font* gFont;

#endif //_GLOBALS_H_
