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
#include "entitymanager.h"
#include "globals.h"
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
  std::forward_list<Collision> collisions = find_collisions();
  for (auto collision : collisions) {
    entt::entity entity = collision.first;
    entt::entity other = collision.second;

    switch (ecs_->get<Type>(entity)) {
    case ENTITY_TYPE_ENEMY: {
      // Push away from other zombies
      if (ecs_->get<Type>(other) == ENTITY_TYPE_ENEMY) {
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

      // Push away from the player
      if (ecs_->get<Type>(other) == ENTITY_TYPE_PLAYER) {
        Position posOther = ecs_->get<Position>(other);
        Position &posSelf = ecs_->get<Position>(entity);
        float dx = posOther.x - posSelf.x;
        float dy = posOther.y - posSelf.y;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if (distance < 32) {
          double angle = atan2(dy, dx);
          Velocity &velocity = ecs_->get<Velocity>(entity);
          velocity.add(-0.6, angle);
          Velocity &vplayer = ecs_->get<Velocity>(other);
          vplayer.add(0.8, angle);
          // And inflict damage to the player
          Health &health = ecs_->get<Health>(other);
          health.health -= 1;
          if (health.health <= 0) {
            if (ecs_->all_of<Controllable>(other)) {
              ecs_->remove<Controllable>(other);
              std::cout << "REMOVED" << std::endl;
            }
            Sprite &sprite = ecs_->get<Sprite>(other);
            sprite.rect.x = 64;
          }
        }
      }
      break;
    }

    case ENTITY_TYPE_PLAYER: {
      // Collect ammo
      if (ecs_->get<Type>(other) == ENTITY_TYPE_AMMO) {
        ecs_->emplace<EntityFlag>(other, ENTITY_FLAG_DESTROY);
        game.ammo += 20;
        std::cout << "Ammo collected!" << std::endl;
        std::cout << "Ammo now at " << game.ammo << std::endl;
      }
      break;
    }

    case ENTITY_TYPE_AMMO:
      break;

    default:
      std::cout << "Unhandled collission detected!" << std::endl;
    }
  }

  // Seek player
  // TODO decouple this into some sort of logic component
  auto view = ecs_->view<AI>();
  for (auto entity : view) {
    entt::entity target = view.get<AI>(entity).target;
    Position destination = ecs_->get<Position>(target);
    Position &source = ecs_->get<Position>(entity);
    float dx = destination.x - source.x;
    float dy = destination.y - source.y;
    double angle = atan2(dy, dx);
    Velocity &velocity = ecs_->get<Velocity>(entity);
    velocity.add(Z_SPEED, angle);
    source.rotation = angle;

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

  // Destroy flagged entities
  {
    auto view = ecs_->view<EntityFlag>();
    for (entt::entity entity : view) {
      if (ecs_->get<EntityFlag>(entity) == ENTITY_FLAG_DESTROY) {
        ecs_->destroy(entity);
      }
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
  switch (event) {
  case EVENT_BULLET_FIRED: {
    Line &l = ecs_->get<Line>(entity);
    double angle = atan2(l.y2 - l.y1, l.x2 - l.x1);
    double dist = (l.x2 - l.x1) / cos(angle);
    if (dist < BULLET_RANGE) {
      l.x2 = l.x1 + BULLET_RANGE * cos(angle);
      l.y2 = l.y1 + BULLET_RANGE * sin(angle);
    }

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
        bool inside1 = point_circle({l.x1, l.y1}, {(int)p.x, (int)p.y}, 32);
        bool inside2 = point_circle({l.x2, l.y2}, {(int)p.x, (int)p.y}, 32);
        if (inside1 || inside2) {
          collision = true; // Indicates collision with ends of the line
          distance = sqrt(pow(l.x1 - p.x, 2) + pow(l.y1 - p.y, 2));
          closest = zombie;
          closest_distance = distance;
          collision = true;
          if (distance <= 32) { // Indicates that the zombie is ON the player
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
        // TODO the wrong zombie is sometimes hit, due to how it calculates the point onto the segment
        if (on_segment) { // Indicates that the closest point is within the length of the line
          distance = sqrt(pow(closest_x - p.x, 2) + pow(closest_y - p.y, 2));
          if (distance <= 32) { // Indicates that the closest point collides ON the line
            collision = true;
            //Get the exact collision point
            // TODO the exact point is not calculated properly
            distance = sqrt(pow(closest_x - l.x1, 2) + pow(closest_y - l.y1, 2));
            if (distance < closest_distance) { // If the collision point is closer than any other collision
              closest_distance = distance;
              closest = zombie;
            }
          }
        }
      }
    }
    if (collision) {
      Health &h = ecs_->get<Health>(closest);
      h.health -= 20;
      if (h.health <= 0) {
        std::cout << "Destroying zombie..." << std::endl;
        // TODO decouple this to an event queue, and add graphics for hurt zombies
        ecs_->destroy(closest);
      }
      // Shortening the bullet line
      l.x2 = l.x1 + closest_distance * cos(angle);
      l.y2 = l.y1 + closest_distance * sin(angle);
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
bool Physics::point_circle(SDL_Point p, SDL_Point c, int r) {
  double distance = sqrt(pow(c.x - p.x, 2) + pow(c.y - p.y, 2));
  if (distance <= r) return true;
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

/* Returns a list of all collisions if the form of an array containing
   [source entity, other entity] */
std::forward_list<Collision> Physics::find_collisions(void) {
  std::forward_list<Collision> collisions;
  auto view = ecs_->view<Position>(entt::exclude<Line>); // (all entities but bullets)
  for (entt::entity entity : view) {
    for (entt::entity other : view) {
      if (entity != other){
        auto entity_box = ecs_->get<HitBox>(entity);
        auto other_box = ecs_->get<HitBox>(other);
        if (calc_collision(entity_box, other_box)) {
          collisions.push_front({entity, other});
        }
      }
    }
  }
  return collisions;
}
