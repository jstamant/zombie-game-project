#include <SDL2/SDL.h>
#include <entt/entt.hpp>

#include "controllable.h"
#include "defines.h"
#include "entitymanager.h"
#include "globals.h"
#include "inputsystem.h"
#include "position.h"
#include "velocity.h"

//DEBUG
#include <iostream>

void InputSystem::init()
{
    std::cout << "InputSystem init()" << std::endl;
}

/* Process all events on the event queue until it is empty.
 */
void processAllEvents(entt::registry* ecs, EntityManager* em)
{
    //First, process the SDL event queue
    while (SDL_PollEvent(&gEventQueue) != 0)
    {
        //User requests quit
        if (gEventQueue.type == SDL_QUIT) {
            gGame.running = false;
        }
        //User presses escape
        if (gEventQueue.type == SDL_KEYDOWN) {
            if (gEventQueue.key.keysym.sym == SDLK_ESCAPE)
                gGame.running = false;
        }
        //User presses left-click
        if (gEventQueue.type == SDL_MOUSEBUTTONDOWN) {
            if (gEventQueue.button.button == SDL_BUTTON_LEFT) {
                em->createBullet();
            }
        }
    }
    //Then, process the movement keys
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    auto view = ecs->view<Controllable, Velocity, Position>();
    for (entt::entity entity: view) {
        Velocity& v = view.get<Velocity>(entity);
        if (keyboard[SDL_SCANCODE_W])
          v.add_components(0, -SPEED);
        if (keyboard[SDL_SCANCODE_A])
          v.add_components(-SPEED, 0);
        if (keyboard[SDL_SCANCODE_S])
          v.add_components(0, SPEED);
        if (keyboard[SDL_SCANCODE_D])
          v.add_components(SPEED, 0);
        // Rotates the entity (character) to face the mouse pointer.
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);
        ecs->patch<Position>(entity, [&mouse](auto &p) {
          p.rotation = atan2(mouse.y - p.y, mouse.x - p.x);
        });
    }
}
