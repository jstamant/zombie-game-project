//******************************************************************************
// entitymanager.cpp
//******************************************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include <cmath>
#include "defines.h"
#include <deque>
#include "enemy.h"
#include "entity.h"
#include "entitymanager.h"
#include <list>
#include <stack>

//TODO remove this when the dependency for this global is phased-out
extern Character* g_character;

//DEBUG
#include <iostream>

EntityManager::EntityManager(sf::RenderWindow* window, sf::Mouse* mouse) {
    window_ = window;
    mouse_  = mouse;
    character_ = NULL;
    m_collision_point = sf::Vector2f(0, 0);
    for (int i=1; i<=MAX_ENTITIES; i++)
        available_ids.push_back(i);
}

//******************************************************************************
// Access functions
//******************************************************************************

void EntityManager::onNotify(Event event, Entity* entity) {
    switch (event) {
        case SHOOT:
            if (character_)
                character_->shoot();
            break;
        case MOVE_UP:
            if (character_)
                character_->move(0, -SPEED);
            break;
        case MOVE_DOWN:
            if (character_)
                character_->move(0, SPEED);
            break;
        case MOVE_LEFT:
            if (character_)
                character_->move(-SPEED, 0);
            break;
        case MOVE_RIGHT:
            if (character_)
                character_->move(SPEED, 0);
            break;
        case NEW_BULLET:
            //do something;
            break;
        default:
            break;
    }
}

/* Renders the background, and all entities to the window.
 */
void EntityManager::render(void) {
    //Draw the background first
    for (std::list<Entity*>::iterator it=tiles.begin(); it!=tiles.end(); it++) {
        window_->draw(**it);
    }
    //Overlay the entities on the background
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        window_->draw(**it);
    }
}

void EntityManager::new_entity(Entity* entity) {
    entity->set_window(window_);
    entity->set_mouse(mouse_);
    entity->set_entitymanager(this);
    entity->set_id(available_ids.front());
    std::cout << "EM new ID " << entity->get_id() << std::endl;
    available_ids.pop_front();
    if (entity->is_collidable())
        collidables.push_back(entity);
    if (entity->is_pickup())
        pickups.push_back(entity);
    if (entity->is_character())
    {
        character_ = dynamic_cast<Character*>(entity);
        g_character = dynamic_cast<Character*>(entity);
    }
    entities.push_back(entity);
    notify(NEW_ENTITY, entity);
}

/* Add an entity to the purge list for later removal.
 * Entities can't be deleted during the update() loop, because the iterator in
 * the update() loop will no longer point to the next entity.
 * @param id: ID of the entity for removal
 */
void EntityManager::del_entity(int id) {
    purge_list.push(id);
    available_ids.push_back(id);
}

/* Remove entities slated for removal.
 * TODO fix how this function is inefficiently searching through the collidables
 * list, even if the entity is not a collidable
 */
void EntityManager::purge(void) {
    int delete_id = 0;
    while (!purge_list.empty()) {
        delete_id = purge_list.top();
        purge_list.pop();
        for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
            if ( (*it)->get_id() == delete_id ) {
                notify(KILL_ENTITY, *it);
                delete *it;
                entities.erase(it);
                break;
            }
        }
        for (std::list<Entity*>::iterator it=collidables.begin(); it!=collidables.end(); it++) {
            if ( (*it)->get_id() == delete_id ) {
                collidables.erase(it);
                break;
            }
        }
        for (std::list<Entity*>::iterator it=pickups.begin(); it!=pickups.end(); it++) {
            if ( (*it)->get_id() == delete_id ) {
                pickups.erase(it);
                break;
            }
        }
    }
}

/* void EntityManager::update_all(void)
 * Updates the logic of all its tracked entities.
 */
void EntityManager::update_all(void) {
    purge();
    for (std::list<Entity*>::iterator it=entities.begin(); it!=entities.end(); it++) {
        (*it)->update_logic();
    }
}

/* Check collisions of a rect with all collidables.
 * @param rect: Rectangle to check collisions with all collidables
 * @return list: List of all entities that collide with the input rect
 */
std::list<Entity*> EntityManager::check_collisions(sf::FloatRect rect) {
    std::list<Entity*> collision_list;
    for (std::list<Entity*>::iterator it=collidables.begin(); it!=collidables.end(); it++) {
        if ((*it)->get_rect()->intersects(rect))
            collision_list.push_back(*it);
    }
    return collision_list;
}

/* Checks collisions of a rect with all pickups.
 * @param Rectable to check collisions with pickups
 * @return List of all pickups that collide with the input rect
 */
std::list<Entity*> EntityManager::check_collisions_pickups(sf::FloatRect rect)
{
    std::list<Entity*> pickup_list;
    for (std::list<Entity*>::iterator it=pickups.begin(); it!=pickups.end(); it++) {
        if ((*it)->get_rect()->intersects(rect))
            pickup_list.push_back(*it);
    }
    return pickup_list;
}

/* Find all collision with a line. Collisions will be listed in order from
 * source to destination.
 * @param Point from where to start the collision detection.
 * @param Point where the collision detection finishes.
 * @return A list of entities whose rects collide with the line.
 * TODO the returned list is bloated with re-occurences of collisions. This is
 * from generating a collision for every pixel of collision.
 * TODO this checks if the entity is a character, so it's tailored for bullet
 * collision; which may or may not be out of the scope of this function...
 */
std::list<Entity*> EntityManager::collision_line(sf::Vector2f source, sf::Vector2f dest) {
    std::list<Entity*> collision_list;
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
        for (std::list<Entity*>::iterator it=collidables.begin(); it!=collidables.end(); it++) {
            if ((*it)->get_rect()->contains(check_x, check_y)) {
                if ( !(*it)->is_character() ) {
                    collision_list.push_back(*it);
                    if (m_collision_point == sf::Vector2f(0, 0))
                        m_collision_point = sf::Vector2f(check_x, check_y);
                }
            }
        }
        //Check next point in the line
        check_x += step_x;
        check_y += step_y;
    }
    return collision_list;
}

/* Returns, and resets the last collision_point.
 */
sf::Vector2f EntityManager::pop_collision_point(void) {
    sf::Vector2f collision_point = m_collision_point;
    m_collision_point = sf::Vector2f(0, 0);
    return collision_point;
}

/* Adds a background tile to the list.
 */
void EntityManager::new_tile(Entity* tile) {
    tile->set_window(window_);
    tile->set_mouse(mouse_);
    tile->set_entitymanager(this);
    tiles.push_back(tile);
}

