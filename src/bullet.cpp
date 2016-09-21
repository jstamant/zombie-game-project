//******************************************************************************
// bullet.cpp
//******************************************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "defines.h"
#include "entity.h"
#include "entitymanager.h"
#include <list>
#include <cmath>

//DEBUG
#include <iostream>

Bullet::Bullet(sf::Vector2f p1, sf::Vector2f p2):
    //TODO: need to figure out why I need to initialize this here...
    line(sf::Lines, 2) {
    time_to_live = BULLET_FLASH_DURATION;
    line[0].position = p1;
    line[1].position = p2;
    line[0].color = sf::Color::Yellow;
    line[1].color = sf::Color::Yellow;
    rect_ = line.getBounds();
    //notify(NEW_BULLET, id_);
    checked_collisions = false;
    extend_line();
}

//******************************************************************************
// Access functions
//******************************************************************************

sf::VertexArray Bullet::get_line(void) { return line; }
void Bullet::setEndpoint(sf::Vector2f point) { line[1].position = point; }

void Bullet::update_logic(void) {
    /*
    if (!checked_collisions) {
        //find_potential_collisions();
        //find_first_collision();
        collision_list = entitymanager_->collision_line(line[0].position, line[1].position);
        if ( !collision_list.empty() ) {
            collision_list.front()->take_damage(20);
            line[1].position = entitymanager_->pop_collision_point();
            collision_list.clear();
        }
        checked_collisions = true;
    }
    */
    if (--time_to_live == 0) {
        entitymanager_->del_entity(id_);
    }
}

/* Override the default implementation from class Entity, in order to draw the
 * bullet's line by default.
 */
void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(line);
}

/* Gets the entity manager to provide a list of potential collisions.
 */
void Bullet::find_potential_collisions(void) {
    collision_list = entitymanager_->check_collisions(rect_);
}

/* Find the first collision along the bullet's path.
 */
void Bullet::find_first_collision(void) {
    std::cout << "First collision:\n";
    float dx = line[1].position.x - line[0].position.x;
    float step_x = dx/BULLET_RANGE;
    float dy = line[1].position.y - line[0].position.y;
    float step_y = dy/BULLET_RANGE;
    //For every point along line:
    float check_x = line[0].position.x;
    float check_y = line[0].position.y;
    for (int i=0; i<BULLET_RANGE; i++) {
        //Check collisions at check_x,check_y
        for (std::list<Entity*>::iterator it=collision_list.begin(); it!=collision_list.end(); it++) {
            if ((*it)->get_rect()->contains(check_x, check_y)) {
                if ( (*it)->is_character() ) {
                    std::cout << "Character!\n";
                    return;
                }
                if ( !(*it==this) ) {
                    //Trim bullet
                    //DEBUG
                    std::cout << "HIT?\n";
                    //DEBUG
                    line[1].position = sf::Vector2f(check_x, check_y);
                    return;
                }else{
                    std::cout << "Bullet!\n";
                }
            }
        }

        //Check next point in the line
        check_x += step_x;
        check_y += step_y;
    }
}

/* Extends or trims the bullet line to the global maximum bullet range.
 */
void Bullet::extend_line(void) {
    sf::Vector2f source = line[0].position;
    sf::Vector2f destination = line[1].position;
    float dx = destination.x - source.x;
    float dy = destination.y - source.y;
    float distance = sqrt(pow(dx,2) + pow(dy,2));
    float distance_ratio = BULLET_RANGE/distance;

    float new_dx = distance_ratio*dx;
    float new_dy = distance_ratio*dy;

    //Extend or trim the bullet line
    sf::Vector2f new_destination = line[0].position + sf::Vector2f(new_dx, new_dy);
    line[1].position = new_destination;
}

bool Bullet::is_bullet(void) { return true; }

