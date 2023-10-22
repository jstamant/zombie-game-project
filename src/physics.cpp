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
#include "velocity.h"

// DEBUG
#include <iostream>

Physics::Physics(entt::registry* registry) {
  ecs_ = registry;
}

void Physics::evaluate(void) {
  auto view = ecs_->view<AI>();
  for (auto entity : view) {
    // Seek player
    entt::entity target = view.get<AI>(entity).target;
    Position destination = ecs_->get<Position>(target);
    Position &source = ecs_->get<Position>(entity);
    float dx = destination.x - source.x;
    float dy = destination.y - source.y;
    double angle = atan2(dy, dx);
    Velocity &velocity = ecs_->get<Velocity>(entity);
    velocity.add(Z_SPEED, angle);
    source.rotation = angle;

    // Push away from other zombies
    {
      auto view = ecs_->view<AI>();
      for (auto other : view) {
        if (other != entity) {
          Position posOther = ecs_->get<Position>(other);
          Position &posSelf = ecs_->get<Position>(entity);
          double dx = posOther.x - posSelf.x;
          double dy = posOther.y - posSelf.y;
          double distance = sqrt(pow(dx, 2) + pow(dy, 2));
          if (distance < 24) {
            double angle = atan2(dy, dx);
            Velocity &velocity = ecs_->get<Velocity>(entity);
            velocity.add(-0.2, angle);
            Velocity &vother = ecs_->get<Velocity>(other);
            vother.add(0.2, angle);
          }
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
          double angle = atan2(dy, dx);
          Velocity &velocity = ecs_->get<Velocity>(entity);
          velocity.add(-0.6, angle);
          Velocity &vplayer = ecs_->get<Velocity>(player);
          vplayer.add(0.8, angle);
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

/* Apply velocity vectors to next position of all entities */
void Physics::apply_velocities(void) {
  auto view = ecs_->view<Position, Velocity>();
  for (entt::entity entity : view) {
    Velocity &v = ecs_->get<Velocity>(entity);
    ecs_->patch<Position>(entity, [&v](auto &p) {
      p.x += v.get_x();
      p.y += v.get_y();
    });
    ecs_->patch<Velocity>(entity, [](auto &v) { v.reset(); });
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
