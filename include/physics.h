#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <entt/entt.hpp>

class Physics
{
public:
  Physics(entt::registry*);
  void evaluate(void);
private:
  entt::registry* ecs;
};

#endif //_PHYSICS_H_
