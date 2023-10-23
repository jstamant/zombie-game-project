//******************************************************************************
// physics.cpp
//******************************************************************************

#include <cmath>
#include <SDL2/SDL.h>
#include <entt/entt.hpp>

#include "ai.h"
#include "controllable.h"
#include "defines.h"
#include "health.h"
#include "line.h"
#include "physics.h"
#include "position.h"
#include "sprite.h"
#include "ttl.h"
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
  {
    auto view = ecs_->view<TTL>();
    for (entt::entity entity : view) {
      TTL &ttl = view.get<TTL>(entity);
      if (ttl-- <= 0)
        ecs_->destroy(entity);
    }
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
  case BULLET_FIRED: {
    std::cout << "TODO - calculating bullet trajectory" << std::endl;
    std::cout << "Just travelling max distance" << std::endl;
    Line &l = ecs_->get<Line>(entity);
    double angle = atan2(l.y2 - l.y1, l.x2 - l.x1);
    double dist = (l.x2 - l.x1) / cos(angle);
    if (dist < BULLET_RANGE) {
      l.x2 = l.x1 + BULLET_RANGE * cos(angle);
      l.y2 = l.y1 + BULLET_RANGE * sin(angle);
    }
    // Bullet &bullet = ecs_->get<Bullet>(entity);
    // Position &p = ecs_->get<Position>(entity);
    // SDL_Rect bullet_bounds;
    // bullet_bounds.x = p.x;
    // bullet_bounds.y = p.y;
    // bullet_bounds.w = bullet.target.x - p.x;
    // bullet_bounds.h = bullet.target.y - p.y;
    // std::cout << bullet_bounds.x << std::endl;
    // std::cout << bullet_bounds.y << std::endl;
    // std::cout << bullet_bounds.w << std::endl;
    // std::cout << bullet_bounds.h << std::endl;
    // auto view = ecs_->view<AI>();
    // for (entt::entity zombie : view) {
    //   Sprite sprite = ecs_->get<Sprite>(zombie);
    //   if (calc_collision(bullet_bounds, sprite.rect)) {
    //     // std::cout << "potential collission" << std::endl;
    //   }
    // }
    break;
  }
  case ENEMY_CREATED:
    std::cout << "New enemy!" << std::endl;
    break;
  default:
    std::cout << "No recognizable event found" << std::endl;
  }
}

bool Physics::calc_collision(SDL_Rect r1, SDL_Rect r2) {
  if (r2.x <= r1.x + r1.w && r2.y <= r1.y + r1.h && r1.x <= r2.x + r2.w &&
      r1.y <= r2.y + r2.h) {
    // std::cout << "collision found" << std::endl;
    return true;
  }
  return false;
}
