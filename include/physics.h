#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <entt/entt.hpp>
#include "observer.h"

class Physics : public Observer
{
public:
  Physics(entt::registry*);
  void evaluate(void);
  void apply_velocities(void);
  virtual void onNotify(entt::entity, Event);
private:
  entt::registry* ecs_;
};

#endif //_PHYSICS_H_
