#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <forward_list>
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include <utility>

#include "observer.h"

typedef std::pair<entt::entity, entt::entity> Collision;

class Physics : public Observer {
public:
  Physics(entt::registry *);
  void evaluate(void);
  void apply_velocities(void);
  virtual void onNotify(entt::entity, Event);
  bool calc_collision(SDL_Rect, SDL_Rect);
  bool line_point(int, int, int, int, int, int);

private:
  entt::registry *ecs_;
  std::forward_list<Collision> find_collisions(void);
  template <typename T>
  std::forward_list<Collision> find_collisions_to(SDL_Rect);
  bool point_circle(SDL_Point, SDL_Point, int);
};

#endif //_PHYSICS_H_
