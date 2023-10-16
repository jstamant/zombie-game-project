//******************************************************************************
// entitymanager.cpp
//******************************************************************************

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

// DEBUG
#include <iostream>

EntityManager::EntityManager(entt::registry* registry) {
    registry_ = registry;
}

void EntityManager::createBullet(void) {
    // Make sure the player is actually alive, or seg fault will
    // happen, since view<Controllable> will return empty when the
    // player has its control removed
    entt::entity playerID = registry_->view<Controllable>().front();
    if (registry_->valid(playerID)) {
        std::cout << "SHOOT!" << std::endl;
        Position &playerPos = registry_->get<Position>(playerID);
        SDL_Point source = {(int)playerPos.x, (int)playerPos.y};
        SDL_Point target = {gEventQueue.button.x, gEventQueue.button.y};
        entt::entity bulletID = registry_->create();
        Bullet &bullet = registry_->emplace<Bullet>(bulletID, source, target);
    }
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
