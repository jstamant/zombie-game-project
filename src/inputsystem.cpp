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

InputSystem::InputSystem(entt::registry *registry, EntityManager *em,
                         SDL_Event *events) {
  ecs_ = registry;
  em_ = em;
  event_queue_ = events;
}

/* Process all events on the event queue until it is empty.
 */
void InputSystem::processAllEvents(void) {
  // First, process the SDL event queue
  while (SDL_PollEvent(event_queue_) != 0) {
    // User requests quit
    if (event_queue_->type == SDL_QUIT) {
      game.running = false;
    }
    // User presses escape
    if (event_queue_->type == SDL_KEYDOWN) {
      if (event_queue_->key.keysym.sym == SDLK_ESCAPE)
        game.running = false;
    }
    // User presses left-click
    if (event_queue_->type == SDL_MOUSEBUTTONDOWN) {
      if (event_queue_->button.button == SDL_BUTTON_LEFT) {
        if (game.ammo > 0) {
          em_->createBullet({event_queue_->button.x, event_queue_->button.y});
          game.ammo--;
        }
      }
    }
  }
  // Then, process the movement keys
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  auto view = ecs_->view<Controllable, Velocity, Position>();
  for (entt::entity entity : view) {
    Velocity &v = view.get<Velocity>(entity);
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
    ecs_->patch<Position>(entity, [&mouse](auto &p) {
      // Works according to local (screen) coordinates
      p.rotation =
          atan2(mouse.y - WINDOW_HEIGHT / 2, mouse.x - WINDOW_WIDTH / 2);
    });
  }
}
