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
#include "bullet.h"
#include "controllable.h"
#include "health.h"
#include "position.h"
#include "renderable.h"
#include "sprite.h"
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
    entt::entity entity = registry_->create();
    registry_->emplace<Renderable>(entity);
    Position &p = registry_->emplace<Position>(entity);
    Position &playerPos = registry_->get<Position>(player);
    p.x = (int)playerPos.x;
    p.y = (int)playerPos.y;
    SDL_Point target = {gEventQueue.button.x, gEventQueue.button.y};
    p.rotation = atan2(target.y - p.y, target.x - p.x);
    registry_->emplace<Bullet>(entity, target);
    notify(entity, BULLET_FIRED);
  }
}

entt::entity EntityManager::createPlayer(void) {
  entt::entity player = registry_->create();
  registry_->emplace<Renderable>(player);
  registry_->emplace<Velocity>(player);
  registry_->emplace<Sprite>(player);
  registry_->emplace<Position>(player, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
  registry_->emplace<Controllable>(player, true);
  registry_->emplace<Health>(player);
  return player;
}

entt::entity EntityManager::createZombie(entt::entity target) {
  entt::entity zombie = registry_->create();
  registry_->emplace<Renderable>(zombie);
  registry_->emplace<Velocity>(zombie);
  registry_->emplace<Sprite>(zombie).setRow(1);
  registry_->emplace<Position>(zombie, WINDOW_WIDTH + 100,
                               rand() % WINDOW_HEIGHT);
  registry_->emplace<AI>(zombie).target = target;
  registry_->emplace<Health>(zombie);
  return zombie;
}
