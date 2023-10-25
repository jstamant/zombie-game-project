//******************************************************************************
// physics.cpp
//******************************************************************************

#include <cmath>
#include <forward_list>
#include <SDL2/SDL.h>
#include <entt/entt.hpp>

#include "ai.h"
#include "controllable.h"
#include "defines.h"
#include "health.h"
#include "hitbox.h"
#include "line.h"
#include "physics.h"
#include "position.h"
#include "sprite.h"
#include "ttl.h"
#include "type.h"
#include "velocity.h"

// DEBUG
#include <iostream>
#include <sys/types.h>

Physics::Physics(entt::registry* registry) {
  ecs_ = registry;
}

void Physics::evaluate(void) {
  std::forward_list<entt::entity> collisions = find_collisions();
  for (auto entity : collisions) {
    if (ecs_->get<Type>(entity) == ENTITY_TYPE_AMMO)
      std::cout << "AMMO HAS A COLLISION!" << std::endl;
  }

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
    Position &p = ecs_->get<Position>(entity);
    Sprite &s = ecs_->get<Sprite>(entity);
    ecs_->patch<HitBox>(entity, [&p, &s](auto &b) {
      b.x = p.x - s.offsetX;
      b.y = p.y - s.offsetY;
    });
    ecs_->patch<Velocity>(entity, [](auto &v) { v.reset(); });
  }
}

void Physics::onNotify(entt::entity entity, Event event) {
  std::cout << "Physics manager notified!" << std::endl;
  switch (event) {
  case EVENT_BULLET_FIRED: {
    // TODO - seg faults when the tip of the line hits only one zombie
    std::cout << "calculating bullet trajectory" << std::endl;
    Line &l = ecs_->get<Line>(entity);
    double angle = atan2(l.y2 - l.y1, l.x2 - l.x1);
    double dist = (l.x2 - l.x1) / cos(angle);
    // if (dist < BULLET_RANGE) {
    //   l.x2 = l.x1 + BULLET_RANGE * cos(angle);
    //   l.y2 = l.y1 + BULLET_RANGE * sin(angle);
    // }
    SDL_Rect bullet_bounds;
    // This is required to make the hitbox always positive
    if (l.x1 < l.x2) {
      bullet_bounds.x = l.x1;
      bullet_bounds.w = l.x2 - l.x1;
    } else {
      bullet_bounds.x = l.x2;
      bullet_bounds.w = l.x1 - l.x2;
    }
    if (l.y1 < l.y2) {
      bullet_bounds.y = l.y1;
      bullet_bounds.h = l.y2 - l.y1;
    } else {
      bullet_bounds.y = l.y2;
      bullet_bounds.h = l.y1 - l.y2;
    }
    auto view = ecs_->view<AI>();
    entt::entity closest;
    double closest_distance = HUGE_VAL;
    double distance;
    bool collision = false;
    for (entt::entity zombie : view) {
      HitBox box = ecs_->get<HitBox>(zombie);
      Position p = ecs_->get<Position>(zombie);
      if (calc_collision(bullet_bounds, box)) {
        std::cout << "potential collission, looking at line collision" << std::endl;
        bool inside1 = point_circle(l.x1, l.y1, p.x, p.y, 32);
        bool inside2 = point_circle(l.x2, l.y2, p.x, p.y, 32);
        if (inside1 || inside2) {
          // TODO need to properly take care of this case. I don't check properly
          std::cout << "collision on endpoint!" << std::endl;
          collision = true; // Indicates collision with ends of the line
          distance = sqrt(pow(l.x1-p.x,2) + pow(l.y1-p.y,2));
          if (distance <=32) { // Indicates that the zombie is ON the player
            std::cout << "collision on CLOSE endpoint!" << std::endl;
            closest = zombie;
            collision = true;
            break;
          }
        }
        float length = sqrt(pow(l.x2 - l.x1, 2) + pow(l.y2 - l.y1, 2));
        float dot =
            (((p.x - l.x1) * (l.x2 - l.x1)) + ((p.y - l.y1) * (l.y2 - l.y1))) /
            pow(length, 2);
        float closest_x = l.x1 + (dot * (l.x2 - l.x1));
        float closest_y = l.y1 + (dot * (l.y2 - l.y1));
        bool on_segment = line_point(l.x1, l.y1, l.x2, l.y2, closest_x, closest_y);
        if (on_segment) { // Indicates that the closest point is within the length of the line
          std::cout << "somewhere between segment!" << std::endl;
          distance = sqrt(pow(closest_x - p.x, 2) + pow(closest_y - p.y, 2));
          if (distance <= 32) { // Indicates that the closest point collides ON the line
            collision = true;
            std::cout << "collision on segment!" << std::endl;
            //Get the exact collision point
            distance = sqrt(pow(closest_x - l.x1, 2) + pow(closest_y - l.y1, 2));
            if (distance < closest_distance) { // If the collision point is closer than any other collision
              std::cout << "new closest found!" << std::endl
                        << "coordinates: " << closest_x << " " << closest_y
                        << std::endl;
              closest_distance = distance;
              closest = zombie;
            }
          }
        }
      }
    }
    if (collision) {
      std::cout << "THERE WAS A COLLISION" << &closest << std::endl;
      std::cout << "closest is " << &closest << std::endl;
      std::cout << "closest dist is " << closest_distance << std::endl;
      Health &h = ecs_->get<Health>(closest);
      std::cout << "Health before: " << h.health << std::endl;
      h.health -= 20;
      std::cout << "Health after: " << h.health << std::endl;
      if (h.health <= 0) {
        std::cout << "Destroying entity..." << std::endl;
        ecs_->destroy(closest);
      }
      std::cout << "Shortening the bullet line..." << std::endl;
      l.x2 = l.x1 + closest_distance * cos(angle);
      l.y2 = l.y1 + closest_distance * sin(angle);
      std::cout << "done" << std::endl;
    } else {
      std::cout << "There was NO collision" << std::endl;
    }
    break;
  }
  case EVENT_ENEMY_CREATED:
    std::cout << "New enemy!" << std::endl;
    break;
  default:
    std::cout << "No recognizable event found" << std::endl;
  }
}

bool Physics::calc_collision(SDL_Rect r1, SDL_Rect r2) {
  if (r2.x <= r1.x + r1.w && r2.x + r2.w >= r1.x && r2.y <= r1.y + r1.h &&
      r2.y + r2.h >= r1.y) {
    return true;
  }
  return false;
}

/* Checks if a point is inside a circle */
bool Physics::point_circle(int x, int y, int cx, int cy, int r) {
  double distance = sqrt(pow(cx - x, 2) + pow(cy - y, 2));
  if (distance <= r)
    return true;
  return false;
}

/* Checks if a point is on a line */
bool Physics::line_point(int x1, int y1, int x2, int y2, int closest_x, int closest_y) {
  double d1 = sqrt(pow(x1 - closest_x, 2) + pow(y1 - closest_y, 2));
  double d2 = sqrt(pow(x2 - closest_x, 2) + pow(y2 - closest_y, 2));
  double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  double buffer = 1.0;
  if (d1 + d2 >= length - buffer && d1 + d2 <= length + buffer)
    return true;
  return false;
}

std::forward_list<entt::entity> Physics::find_collisions(void) {
  std::forward_list<entt::entity> collisions;
  auto view = ecs_->view<Position>(entt::exclude<Line>); // All entities but bullets
  for (entt::entity entity : view) {
    for (entt::entity other : view) {
      if (entity != other){
        auto entity_box = ecs_->get<HitBox>(entity);
        auto other_box = ecs_->get<HitBox>(other);
        if (calc_collision(entity_box, other_box)) {
          collisions.push_front(entity);
        }
      }
    }
  }
  return collisions;
}
