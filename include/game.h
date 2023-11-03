#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

class Game {
public:
  Game();
  bool running;
  int ammo = 20;
  void close(void);
  SDL_Event *get_event_queue(void);
  SDL_Renderer *get_renderer(void);
  SDL_Surface *get_surface(void);
  SDL_Window *get_window(void);
  bool initializeSDL(void);

private:
  SDL_Event event_queue_;
  SDL_Renderer *renderer_;
  SDL_Surface *surface_;
  SDL_Window *window_;
};

#endif //_GAME_H_
