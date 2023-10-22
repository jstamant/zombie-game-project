//************************************************
// main.cpp
//************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //FOR TESTING IN THIS MONOLITHIC FILE

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
SDL_Window* gWindow = NULL;         //The window we'll be rendering to

//FOR TESTING, global function declerations TO BE MOVED OR REMOVED
//Frees media and shuts down SDL
void close();
SDL_Surface* loadSurface(std::string);

int main(void)
{

  Velocity vel;
  std::cout << "x: " << vel.get_x() << std::endl;
  std::cout << "y: " << vel.get_y() << std::endl;
  vel.add(2, M_PI_2);
  std::cout << "x: " << vel.get_x() << std::endl;
  std::cout << "y: " << vel.get_y() << std::endl;
  vel.add(4, -M_PI_2);
  std::cout << "x: " << vel.get_x() << std::endl;
  std::cout << "y: " << vel.get_y() << std::endl;

  // TESTING STUFF TO INITIALIZE FOR TESTING
  entt::registry registry;
  EntityManager entitymanager(&registry);
  int enemy_spawn = 0;
  srand(time(NULL));

  // Start up SDL and create the window
  if (!initializeSDL())
    printf("Failed to initialize SDL!\n");

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

    // Perform game logic
    physics.evaluate();
    // Update positions
    physics.apply_velocities();

    // Perform rendering
    renderAll(gRenderer, &registry);
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
