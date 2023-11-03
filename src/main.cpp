//************************************************
// main.cpp
//************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Include std dependencies
#include <cmath>
#include <iostream>
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

//Make these variables global for now...
Game game;
SDL_Event event_queue_;              //The event queue for the entire game
SDL_Texture* gTextTexture = NULL;
TTF_Font* gFont = NULL;

// TODO - move these functions, they shouldn't really be global
//Frees media and shuts down SDL
SDL_Surface* loadSurface(std::string);
bool loadMedia(void);

int main(void)
{
  entt::registry registry;
  EntityManager entitymanager(&registry);
  int enemy_spawn = 0;
  int ammo_spawn = 0;
  srand(time(NULL));

  // Start up SDL and create the window
  if (!game.initializeSDL())
    printf("Failed to initialize SDL!\n");
  RenderSystem render_system(game.get_renderer(), &registry);
  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }
  loadMedia();

  // Initialize some system(s)
  Physics physics(&registry);
  entitymanager.addObserver(&physics);
  InputSystem input_system(&registry, &entitymanager, game.get_event_queue());

  entt::entity player = entitymanager.createPlayer();

  // Add some zombies
  for (int i = 0; i < 100; i++)
    entitymanager.createZombie(player);

  // While game is running; main game loop
  game.running = true;
  while (game.running) {
    // Process input and/or events
    input_system.processAllEvents();

    // Spawn enemies and ammo
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
  game.close();

  return 0;
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
        optimizedSurface = SDL_ConvertSurface(loadedSurface, game.get_surface()->format, 0);
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
