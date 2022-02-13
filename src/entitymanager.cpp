//******************************************************************************
// entitymanager.cpp
//******************************************************************************

#include "defines.h"
#include "entitymanager.h"
#include <entt/entt.hpp>

//Include component header files
#include "ai.h"
#include "controllable.h"
#include "health.h"
#include "position.h"
#include "renderable.h"

EntityManager::EntityManager(entt::registry* registry) {
    registry_ = registry;
}

entt::entity EntityManager::createPlayer(void) {
    entt::entity player = registry_->create();
    registry_->emplace<Renderable>(player);
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
    Renderable& r = registry_->emplace<Renderable>(zombie);
    r.sprite.setRow(1);
    Position& p = registry_->emplace<Position>(zombie);
    p.x = WINDOW_WIDTH+100;
    p.y = rand()%WINDOW_HEIGHT;
    AI& ai =registry_->emplace<AI>(zombie);
    ai.target = target;
    registry_->emplace<Health>(zombie);
    return zombie;
}
