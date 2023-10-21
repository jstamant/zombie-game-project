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
  ecs_ = registry;
}

void Physics::evaluate(void) {
  // TODO these need to be velocity vectors that operate on the position at the END.
  auto view = ecs_->view<AI>();
  for (auto entity : view) {
    {
      // Seek player
      entt::entity target = view.get<AI>(entity).target;
      Position destination = ecs_->get<Position>(target);
      Position &source = ecs_->get<Position>(entity);
      float dx = destination.x - source.x;
      float dy = destination.y - source.y;
      double raw_angle = atan2(dy, dx);
      float move_x = Z_SPEED * cos(raw_angle);
      float move_y = Z_SPEED * sin(raw_angle);
      source.next.rotation = raw_angle * 180 / M_PI;
      // Perform movement
      source.next.x += move_x;
      source.next.y += move_y;
    }
    // Push away from other zombies
    auto nestedview = ecs_->view<AI>();
    for (auto other : nestedview) {
      if (entity != other) {
        Position posOther = ecs_->get<Position>(other);
        Position &posSelf = ecs_->get<Position>(entity);
        float dx = posOther.x - posSelf.x;
        float dy = posOther.y - posSelf.y;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance < 24) {
          double angle =
              atan2(dy, dx) + M_PI; // Angle pointing away from the other zombie
          posSelf.next.x += 0.8 * cos(angle);
          posSelf.next.y += 0.8 * sin(angle);
        }
      }
    }
    // Push away from the player
    entt::entity player = ecs_->view<Controllable>().front();
    if (ecs_->valid(player)) {
      if (entity != player) {
        Position posOther = ecs_->get<Position>(player);
        Position &posSelf = ecs_->get<Position>(entity);
        float dx = posOther.x - posSelf.x;
        float dy = posOther.y - posSelf.y;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance < 32) {
          double angle =
              atan2(dy, dx) + M_PI; // Angle pointing away from the other zombie
          posSelf.next.x += 0.6 * cos(angle);
          posSelf.next.y += 0.6 * sin(angle);
          // And inflict damage to the player
          Health &health = ecs_->get<Health>(player);
          health.health -= 1;
          if (health.health <= 0) {
            if (ecs_->all_of<Controllable>(player)) {
              ecs_->remove<Controllable>(player);
              std::cout << "REMOVED" << std::endl;
            }
            Sprite &sprite = ecs_->get<Sprite>(player);
            sprite.rect.x = 64;
          }
        }
      }
    }
  }
  // Expire bullets
  // TODO move ttl to private, once this is in an update function
  auto newview = ecs_->view<Bullet>();
  for (entt::entity bullet : newview) {
    Bullet &b = newview.get<Bullet>(bullet);
    if (b.ttl-- <= 0)
      ecs_->destroy(bullet);
  }

}

void Physics::swap(void) {
  //TODO swap all positions with the next position
  auto view = ecs_->view<Position>();
  for (entt::entity entity : view) {
    //TODO can move this to the entitymanager to manage the swap
    Position& p = view.get<Position>(entity);
    p.swap();
  }
}

void Physics::onNotify(entt::entity entity, Event event) {
  std::cout << "Physics manager notified!" << std::endl;
  switch (event) {
  case BULLET_FIRED:
    std::cout << "TODO - calculating bullet trajectory" << std::endl;
    break;
  case ENEMY_CREATED:
    std::cout << "New enemy!" << std::endl;
    break;
  default:
    std::cout << "No recognizable event found" << std::endl;
  }
}
