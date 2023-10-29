//******************************************************************************
// entitymanager.cpp
//******************************************************************************

#include <cmath>
#include "defines.h"
#include "entitymanager.h"
#include <entt/entt.hpp>
#include "globals.h"

//Include component header files
#include "ai.h"
#include "controllable.h"
#include "health.h"
#include "hitbox.h"
#include "line.h"
#include "position.h"
#include "renderable.h"
#include "sprite.h"
#include "ttl.h"
#include "type.h"
#include "velocity.h"

// DEBUG
#include <iostream>

EntityManager::EntityManager(entt::registry* registry) {
    registry_ = registry;
}

// TODO make this independent of the player when I have a message bus setup
void EntityManager::createBullet(void) {
  // Make sure the player is actually alive, or seg fault will
  // happen, since view<Controllable> will return empty when the
  // player has its control removed
  entt::entity player = registry_->view<Controllable>().front();
  if (registry_->valid(player)) {
    entt::entity bullet = registry_->create();
    registry_->emplace<Renderable>(bullet);
    Position &p = registry_->emplace<Position>(bullet);
    Position &playerPos = registry_->get<Position>(player);
    p.x = (int)playerPos.x;
    p.y = (int)playerPos.y;
    SDL_Point target = {gEventQueue.button.x, gEventQueue.button.y};

    // Translate locale screen coordinates to global coordinates
    target.x += (int)playerPos.x - WINDOW_WIDTH / 2;
    target.y += (int)playerPos.y - WINDOW_HEIGHT / 2;

    p.rotation = atan2(target.y - p.y, target.x - p.x);
    registry_->emplace<Line>(bullet, p.x, p.y, target.x, target.y);
    registry_->emplace<TTL>(bullet, BULLET_FLASH_DURATION);
    notify(bullet, EVENT_BULLET_FIRED);
  }
}

entt::entity EntityManager::createPlayer(void) {
  entt::entity player = registry_->create();
  registry_->emplace<Type>(player, ENTITY_TYPE_PLAYER);
  registry_->emplace<Renderable>(player);
  registry_->emplace<Velocity>(player);
  auto s = registry_->emplace<Sprite>(player);
  auto p = registry_->emplace<Position>(player, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
  SDL_Rect box;
  box.x = p.x - s.offsetX;
  box.y = p.y - s.offsetY;
  box.w = s.rect.w;
  box.h = s.rect.h;
  registry_->emplace<HitBox>(player, box);
  registry_->emplace<Controllable>(player, true);
  registry_->emplace<Health>(player);
  return player;
}

entt::entity EntityManager::createZombie(entt::entity target) {
  entt::entity zombie = registry_->create();
  registry_->emplace<Type>(zombie, ENTITY_TYPE_ENEMY);
  registry_->emplace<Renderable>(zombie);
  registry_->emplace<Velocity>(zombie);
  Sprite &s = registry_->emplace<Sprite>(zombie);
  s.setRow(1);
  Position p = registry_->emplace<Position>(zombie, WINDOW_WIDTH + 100,
                                            rand() % WINDOW_HEIGHT);
  SDL_Rect box;
  box.x = p.x - s.offsetX;
  box.y = p.y - s.offsetY;
  box.w = s.rect.w;
  box.h = s.rect.h;
  registry_->emplace<HitBox>(zombie, box);
  registry_->emplace<AI>(zombie).target = target;
  registry_->emplace<Health>(zombie);
  return zombie;
}

entt::entity EntityManager::create_ammo(void) {
  entt::entity ammo = registry_->create();
  registry_->emplace<Type>(ammo, ENTITY_TYPE_AMMO);
  registry_->emplace<Renderable>(ammo);
  Sprite &s = registry_->emplace<Sprite>(ammo);
  s.setRow(3);
  s.setFrame(1);
  Position &p = registry_->emplace<Position>(ammo);
  p.x = rand() % WINDOW_WIDTH;
  p.y = rand() % WINDOW_HEIGHT;
  SDL_Rect box;
  box.x = p.x - s.offsetX;
  box.y = p.y - s.offsetY;
  box.w = s.rect.w;
  box.h = s.rect.h;
  registry_->emplace<HitBox>(ammo, box);
  return ammo;
}
