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
    std::cout << "SHOOT!" << std::endl;
    entt::entity entity = registry_->create();
    registry_->emplace<Renderable>(entity);
    Position &p = registry_->emplace<Position>(entity);
    Position &playerPos = registry_->get<Position>(player);
    p.x = (int)playerPos.x;
    p.y = (int)playerPos.y;
    SDL_Point target = {gEventQueue.button.x, gEventQueue.button.y};
    p.rotation = atan2(target.y - p.y, target.x - p.x);
    registry_->emplace<Bullet>(entity, target);
  }
}

entt::entity EntityManager::createPlayer(void) {
    entt::entity player = registry_->create();
    registry_->emplace<Renderable>(player);
    registry_->emplace<Sprite>(player);
    Position& p = registry_->emplace<Position>(player);
    p.x = WINDOW_WIDTH/2;
    p.y = WINDOW_HEIGHT/2;
    Controllable& c = registry_->emplace<Controllable>(player);
    c.state = true;
    registry_->emplace<Health>(player);
    return player;
}

entt::entity EntityManager::createZombie(entt::entity target) {
    entt::entity zombie = registry_->create();
    registry_->emplace<Renderable>(zombie);
    Sprite& sprite = registry_->emplace<Sprite>(zombie);
    sprite.setRow(1);
    Position& p = registry_->emplace<Position>(zombie);
    p.x = WINDOW_WIDTH+100;
    p.y = rand()%WINDOW_HEIGHT;
    AI& ai =registry_->emplace<AI>(zombie);
    ai.target = target;
    registry_->emplace<Health>(zombie);
    return zombie;
}
