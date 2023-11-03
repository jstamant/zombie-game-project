#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include <SDL2/SDL.h>
#include <entt/entt.hpp>

#include "entitymanager.h"

class InputSystem {
public:
  InputSystem(entt::registry*, EntityManager*, SDL_Event*);
  void processAllEvents(void);

private:
  EntityManager* em_;
  entt::registry* ecs_;
  SDL_Event* event_queue_;
};


#endif //_INPUTSYSTEM_H_
