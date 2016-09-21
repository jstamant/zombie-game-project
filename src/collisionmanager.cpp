//******************************************************************************
// collisionmanager.cpp
//******************************************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "collisionmanager.h"
#include "defines.h"
#include "entity.h"
#include "math.h"
#include <unordered_map>

//DEBUG
#include <iostream>

//******************************************************************************
// Constructors
//******************************************************************************

CollisionManager::CollisionManager() {
    //RectMap mobileRects_;
    //RectMap allRects_;
}

//******************************************************************************
// Communication functions
//******************************************************************************

void CollisionManager::onNotify(Event event, Entity* entity) {
    switch (event) {
        case NEW_ENTITY:
            registerEntity(entity);
            std::cout << "CollisionManager registered ID " << entity->get_id() << std::endl; //DEBUG
            break;
        case KILL_ENTITY:
            deregisterEntity(entity);
            std::cout << "Deregistered entity " << entity->get_id() << std::endl; //DEBUG
            break;
    }
}

//******************************************************************************
// Access functions
//******************************************************************************

/* Deregisters a given entity by removing it from the collision-checking list.
 * @param entity Entity to deregister
 */
void CollisionManager::deregisterEntity(Entity* entity) {
    int id = entity->get_id();
    if ( entity->is_bullet() ) {
        discreet_.erase(id);
        return;
    }
    if ( !entity->is_solid() )
        mobiles_.erase(id);
    entities_.erase(id);
}

/* Registers a given entity by adding it to the collision-checking list.
 * @param entity Entity to register
 */
void CollisionManager::registerEntity(Entity* entity) {
    int id = entity->get_id();
    EntityPair entityPair(id, entity);
    if ( entity->is_bullet() ) {
        discreet_.insert(entityPair);
        bulletCollision(entity);
        return;
    }
    if ( !entity->is_solid() )
        mobiles_.insert(entityPair);
    entities_.insert(entityPair);
}

//******************************************************************************
// General-purpose functions
//******************************************************************************

/* Checks collisions between an entity and all other game entities.
 * @param entity Entity object to check collisions.
 * @return List of entities that collide with the input entity.
 */
EntityList CollisionManager::checkCollisions(Entity* entity) {
    EntityList collisions;
    for (auto it=entities_.begin(); it!=entities_.end(); it++) {
        if ( it->second->get_rect()->intersects(*(entity->get_rect())) &&
             it->second->get_id() != entity->get_id() )
            collisions.push_back( it->second );
    }
    return collisions;
}

//******************************************************************************
// Discreet collsision functions
//******************************************************************************

/* Checks collisions with a bullet, and all entities
 * Needs refactoring. Badly.
 */
void CollisionManager::bulletCollision(Entity* bullet) {
    EntityList coarseCollisionList = checkCollisions(bullet);
    EntityList fineCollisionList;
    sf::Vector2f source(static_cast<Bullet*>(bullet)->get_line()[0].position);
    sf::Vector2f dest(static_cast<Bullet*>(bullet)->get_line()[1].position);
    sf::Vector2f collisionPoint(0, 0);
    float dx = dest.x - source.x;
    float dy = dest.y - source.y;
    float distance = sqrt(pow(dx,2)+pow(dy,2));
    float step_x = dx/distance;
    float step_y = dy/distance;
    float check_x = source.x;
    float check_y = source.y;
    //For every point along line:
    for (int i=0; i<distance; i++) {
        //Check collisions at (check_x, check_y)
        for (auto it=coarseCollisionList.begin(); it!=coarseCollisionList.end(); it++) {
            if ((*it)->get_rect()->contains(check_x, check_y)) {
                if ( !(*it)->is_character() && !(*it)->is_pickup() ) {
                    fineCollisionList.push_back( *it );
                    if ( collisionPoint == sf::Vector2f(0,0) )
                        collisionPoint = sf::Vector2f(check_x, check_y);
                }
            }
        }
        //Check next point in the line
        check_x += step_x;
        check_y += step_y;
    }
    if ( !fineCollisionList.empty() ) {
        fineCollisionList.front()->take_damage(20);
        static_cast<Bullet*>(bullet)->setEndpoint(collisionPoint);
    }
}

//******************************************************************************
// Update functions
//******************************************************************************

/* Checks all collisions for mobile entities in the game, and stores the list
 * of collisions for any entities that detected collisions (reword this).
 */
void CollisionManager::checkAllCollisions(void) {
    ID id;
    EntityList collisions;
    std::pair<ID,EntityList> entityCollisions;
    //Clear the last check of collisions
    entityCollisionsList_.clear();
    //Check all collisions, and store
    for (auto it=mobiles_.begin(); it!=mobiles_.end(); it++) {
        collisions.clear();
        collisions = checkCollisions( it->second );
        if ( !collisions.empty() ) {
            id = it->first;
            entityCollisions = std::make_pair(id, collisions);
            entityCollisionsList_.insert( entityCollisions );
        }
    }
}

/* Goes through all collisions and acts on them. Typically ran right after
 * checkAllCollisions().
 */
void CollisionManager::processCollisions(void) {
    Entity* entity;
    Entity* other;
    sf::FloatRect* entityRect;
    sf::FloatRect* otherRect;
    sf::FloatRect  intersectRect;
    int ammo;
    //For every entity that we detected collisions
    for (auto it=entityCollisionsList_.begin(); it!=entityCollisionsList_.end(); it++) {
        entity = entities_.at( it->first );
        entityRect = entity->get_rect();
        //Process all of its collisions
        for (auto i=it->second.begin(); i!=it->second.end(); i++) {
            other = *i;
            otherRect = other->get_rect();
            //Run rules for every collsion
            if ( other->is_solid() ) {
                entityRect->intersects(*otherRect, intersectRect);
                //Adjust entity position depending on side of entry
                if ( intersectRect.width < intersectRect.height) {
                    if ( entityRect->left < otherRect->left ) {
                        entity->move(-intersectRect.width, 0);
                    }else{
                        entity->move(intersectRect.width, 0);
                    }
                }else{
                    if ( entityRect->top < otherRect->top ) {
                        entity->move(0, -intersectRect.height);
                    }else{
                        entity->move(0, intersectRect.height);
                    }
                }
            }
            if ( entity->is_character() && other->is_pickup() ) {
                ammo = static_cast<Character*>(entity)->getAmmo();
                static_cast<Character*>(entity)->setAmmo( ammo+20 );
                other->kill();
            }
            if ( entity->is_enemy() && other->is_character() ) {
                other->take_damage(1);
            }
        }
    }
    //Process discreet collisions
    /*
    for (auto it=discreet_.begin(); it!=discreet_.end(); it++) {
        if ( it->second->is_bullet() )
            bulletCollision(it->second);
        discreet_.erase(it);
    }
    */
}

/* Pushes collisions stored in entityCollisionsList_ to the respective entities.
 * To be used in conjunction with checkAllCollisions().
 */
/*
void CollisionManager::pushAllCollisions(void) {
    ID id;
    for (auto it=entityCollisionsList_.begin(); it!=entityCollisionsList_.end(); it++) {
        id = it->first;
        entities_.at(id)->setCollisionList(it->second);
    }
}
*/

