//************************************************
// main.cpp
//************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //FOR TESTING IN THIS MONOLITHIC FILE
#include <SDL2/SDL_ttf.h>

//Include std dependencies
#include <stdlib.h>
#include <time.h>

//Include dependencies
#include <entt/entt.hpp>

#include "ai.h"
#include "defines.h"
#include "entitymanager.h"
#include "functions.h"
#include "game.h"
#include "inputsystem.h"
#include "physics.h"
#include "renderable.h"
#include "rendersystem.h"
#include "velocity.h"

// FOR TESTING
#include <cmath>
#include <iostream>

//Make these variables global for now...
SDL_Event gEventQueue;              //The event queue for the entire game
Game gGame;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Texture* gTextTexture = NULL;
SDL_Window* gWindow = NULL;         //The window we'll be rendering to
TTF_Font* gFont = NULL;

//FOR TESTING, global function declerations TO BE MOVED OR REMOVED
//Frees media and shuts down SDL
void close();
SDL_Surface* loadSurface(std::string);
bool loadMedia(void);

int main(void)
{
  // TESTING STUFF TO INITIALIZE FOR TESTING
  entt::registry registry;
  EntityManager entitymanager(&registry);
  int enemy_spawn = 0;
  int ammo_spawn = 0;
  srand(time(NULL));

  // Start up SDL and create the window
  if (!initializeSDL())
    printf("Failed to initialize SDL!\n");
  RenderSystem render_system(gRenderer, &registry);
  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }
  loadMedia();

  // Initialize some system(s)
  Physics physics(&registry);
  entitymanager.addObserver(&physics);

  entt::entity player = entitymanager.createPlayer();

  // FOR TESTING, add some zombies
  for (int i = 0; i < 100; i++)
    entitymanager.createZombie(player);

  // While game is running; main game loop
  gGame.running = true;
  while (gGame.running) {
    // Process input and/or events
    processAllEvents(&registry, &entitymanager);

    // FOR TESTING
    if (enemy_spawn++ >= 100) {
      entitymanager.createZombie(player);
      enemy_spawn = 0;
    }
    if (ammo_spawn++ >= 500) {
      entitymanager.create_ammo();
      ammo_spawn = 0;
    }

    // Perform game logic
    physics.evaluate();
    // Update positions
    physics.apply_velocities();

    // Perform rendering
    render_system.renderAll();
  }
  //Free resources and close SDL
  close();
  return 0;
}

void close(void)
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Open the font
    gFont = TTF_OpenFont("arial.ttf", 28);
    if (gFont == NULL) {
      printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      success = false;
    } else {
      // Render text
      SDL_Color textColor = {0, 0, 0};
      loadFromRenderedText("testing!", textColor);
      if (!gTextTexture) {
            printf("Failed to render text texture!\n");
            success = false;
      }
    }

    return success;
}
