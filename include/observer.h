#ifndef _OBSERVER_H_
#define _OBSERVER_H_
//************************************************
// observer.h
//************************************************

// Include dependencies
#include "defines.h"
#include <entt/entt.hpp>

class Observer {
public:
  virtual void onNotify(entt::entity, Event) = 0;
};

#endif // _OBSERVER_H_
