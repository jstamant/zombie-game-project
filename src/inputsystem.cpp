#include "bullet.h"
#include "controllable.h"
#include "defines.h"
#include <entt/entt.hpp>
#include "entitymanager.h"
#include "globals.h"
#include "inputsystem.h"
#include <SDL2/SDL.h>
#include "position.h"

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
    auto view = ecs->view<Controllable, Position>();
    for (entt::entity entity: view) {
        Position& p = view.get<Position>(entity);
        if (keyboard[SDL_SCANCODE_W])
            p.next.y -= SPEED;
        if (keyboard[SDL_SCANCODE_A])
            p.next.x -= SPEED;
        if (keyboard[SDL_SCANCODE_S])
            p.next.y += SPEED;
        if (keyboard[SDL_SCANCODE_D])
            p.next.x += SPEED;
        //Rotates the entity (character) to face the mouse pointer.
        SDL_Point mouse_position;
        SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
        SDL_Point angle_vector;
        angle_vector.x = mouse_position.x - p.next.x;
        angle_vector.y = mouse_position.y - p.next.y;
        p.next.rotation = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
    }
}
