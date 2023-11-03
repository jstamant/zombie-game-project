//******************************************************************************
// game.cpp
//******************************************************************************

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "defines.h"
#include "game.h"
#include "globals.h"

Game::Game() {
  SDL_Event event_queue_;
  running = false;
  renderer_ = NULL;
  surface_ = NULL;
  window_ = NULL;
}

void Game::close(void) {
  // Destroy window
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  window_ = NULL;
  renderer_ = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

SDL_Event *Game::get_event_queue(void) { return &event_queue_; }
SDL_Renderer *Game::get_renderer(void) { return renderer_; }
SDL_Surface *Game::get_surface(void) { return surface_; }
SDL_Window *Game::get_window(void) { return window_; }

/* Initialize SDL, and create a window.
   TODO move globals into this class
 */
bool Game::initializeSDL(void)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create window
    window_ = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_ == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create renderer for window
    //Use vsync? I don't have a hard-coded FPS limit, and depend on vsync instead
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    //Initialize renderer color
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    //Initialize PNG loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    //Get window surface
    surface_ = SDL_GetWindowSurface(window_);
    return true;
}

