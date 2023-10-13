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
#include "ai.h"
#include "bullet.h"
#include "controllable.h"
#include "defines.h"
#include "entitymanager.h"
#include <entt/entt.hpp>
#include "functions.h"
#include "game.h"
#include "health.h"
#include "inputsystem.h"
#include "renderable.h"
#include "rendersystem.h"
#include "position.h"

//FOR TESTING
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
    //TESTING STUFF TO INITIALIZE FOR TESTING
    entt::registry registry;
    EntityManager entitymanager(&registry);
    int enemy_spawn = 0;
    srand(time(NULL));

    //Start up SDL and create the window
    if (!initializeSDL())
        printf( "Failed to initialize SDL!\n" );

    entt::entity player = entitymanager.createPlayer();

    //FOR TESTING, add some zombies
    for (int i=0; i<100; i++)
        entitymanager.createZombie(player);

    //While game is running; main game loop
    gGame.running = true;
    while (gGame.running)
    {
        //Process input and/or events
        processAllEvents(&registry);

        //FOR TESTING
        if (enemy_spawn++ >= 100) {
            entitymanager.createZombie(player);
            enemy_spawn = 0;
        }

        //Perform game logic
        //All of the code here needs to be refactored.
        //It's only here while I add/test new code.
        {
            auto view = registry.view<AI>();
            for (auto entity: view) {
                {
                    //Seek player
                    entt::entity target = view.get<AI>(entity).target;
                    Position destination = registry.get<Position>(target);
                    Position& source = registry.get<Position>(entity);
                    float dx = destination.x - source.x;
                    float dy = destination.y - source.y;
                    double raw_angle = atan2(dy, dx);
                    float move_x = Z_SPEED*cos(raw_angle);
                    float move_y = Z_SPEED*sin(raw_angle);
                    source.rotation = raw_angle*180/M_PI;
                    //Perform movement
                    source.x += move_x;
                    source.y += move_y;
                }
                //Push away from other zombies
                auto nestedview = registry.view<AI>();
                for (auto other: nestedview) {
                    if (entity != other) {
                        Position posOther = registry.get<Position>(other);
                        Position& posSelf = registry.get<Position>(entity);
                        float dx = posOther.x - posSelf.x;
                        float dy = posOther.y - posSelf.y;
                        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
                        if (distance < 24) {
                            double angle = atan2(dy, dx) + M_PI; //Angle pointing away from the other zombie
                            posSelf.x += 0.8*cos(angle);
                            posSelf.y += 0.8*sin(angle);
                        }
                    }
                }
                //Push away from the player
                if (entity != player) {
                    Position posOther = registry.get<Position>(player);
                    Position& posSelf = registry.get<Position>(entity);
                    float dx = posOther.x - posSelf.x;
                    float dy = posOther.y - posSelf.y;
                    double distance = sqrt(pow(dx, 2) + pow(dy, 2));
                    if (distance < 32) {
                        double angle = atan2(dy, dx) + M_PI; //Angle pointing away from the other zombie
                        posSelf.x += 0.6*cos(angle);
                        posSelf.y += 0.6*sin(angle);
                        //And inflict damage to the player
                        Health& health = registry.get<Health>(player);
                        health.health -= 1;
                        if (health.health <= 0) {
                            if (registry.all_of<Controllable>(player)) {
                                registry.remove<Controllable>(player);
                                std::cout << "REMOVED" << std::endl;
                            }
                            Renderable& r = registry.get<Renderable>(player);
                            r.sprite.rect.x = 64;
                        }
                    }
                }
            }
            //Expire bullets
            auto newview = registry.view<Bullet>();
            for (entt::entity bullet: newview) {
                Bullet& b = newview.get<Bullet>(bullet);
                if (b.ttl-- <= 0)
                    registry.destroy(bullet);
            }
        }

        //Perform rendering
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
