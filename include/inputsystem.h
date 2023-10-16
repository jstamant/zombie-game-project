#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include <entt/entt.hpp>
#include "entitymanager.h"

class InputSystem
{
public:
    void init(void);
    void processAllEvents(void);
private:
};

void processAllEvents(entt::registry*, EntityManager*);

#endif //_INPUTSYSTEM_H_
