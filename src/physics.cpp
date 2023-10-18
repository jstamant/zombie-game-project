//******************************************************************************
// physics.cpp
//******************************************************************************

#include "ai.h"
#include "bullet.h"
#include "controllable.h"
#include "defines.h"
#include "health.h"
#include <entt/entt.hpp>
#include "physics.h"
#include "position.h"
#include "sprite.h"

// DEBUG
#include <iostream>

Physics::Physics(entt::registry* registry) {
  ecs = registry;
}

void Physics::evaluate(void) {
  auto view = ecs->view<AI>();
  for (auto entity : view) {
    {
      // Seek player
      entt::entity target = view.get<AI>(entity).target;
      Position destination = ecs->get<Position>(target);
      Position &source = ecs->get<Position>(entity);
      float dx = destination.x - source.x;
      float dy = destination.y - source.y;
      double raw_angle = atan2(dy, dx);
      float move_x = Z_SPEED * cos(raw_angle);
      float move_y = Z_SPEED * sin(raw_angle);
      source.rotation = raw_angle * 180 / M_PI;
      // Perform movement
      source.x += move_x;
      source.y += move_y;
    }
    // Push away from other zombies
    auto nestedview = ecs->view<AI>();
    for (auto other : nestedview) {
      if (entity != other) {
        Position posOther = ecs->get<Position>(other);
        Position &posSelf = ecs->get<Position>(entity);
        float dx = posOther.x - posSelf.x;
        float dy = posOther.y - posSelf.y;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance < 24) {
          double angle =
              atan2(dy, dx) + M_PI; // Angle pointing away from the other zombie
          posSelf.x += 0.8 * cos(angle);
          posSelf.y += 0.8 * sin(angle);
        }
      }
    }
    // Push away from the player
    entt::entity player = ecs->view<Controllable>().front();
    if (ecs->valid(player)) {
      if (entity != player) {
        Position posOther = ecs->get<Position>(player);
        Position &posSelf = ecs->get<Position>(entity);
        float dx = posOther.x - posSelf.x;
        float dy = posOther.y - posSelf.y;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance < 32) {
          double angle =
              atan2(dy, dx) + M_PI; // Angle pointing away from the other zombie
          posSelf.x += 0.6 * cos(angle);
          posSelf.y += 0.6 * sin(angle);
          // And inflict damage to the player
          Health &health = ecs->get<Health>(player);
          health.health -= 1;
          if (health.health <= 0) {
            if (ecs->all_of<Controllable>(player)) {
              ecs->remove<Controllable>(player);
              std::cout << "REMOVED" << std::endl;
            }
            Sprite &sprite = ecs->get<Sprite>(player);
            sprite.rect.x = 64;
          }
        }
      }
    }
  }
  // Expire bullets
  // TODO move ttl to private, once this is in an update function
  auto newview = ecs->view<Bullet>();
  for (entt::entity bullet : newview) {
    Bullet &b = newview.get<Bullet>(bullet);
    if (b.ttl-- <= 0)
      ecs->destroy(bullet);
  }
}
