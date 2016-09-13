//************************************************
// bullet.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "defines.h"
#include "entity.h"
#include "entitymanager.h"
#include <list>

Bullet::Bullet(sf::Vector2f p1, sf::Vector2f p2):
    //TODO: need to figure out why I need to initialize this here...
    line(sf::Lines, 2) {
    time_to_live = BULLET_FLASH_DURATION;
    line[0].position = p1;
    line[1].position = p2;
    line[0].color = sf::Color::Yellow;
    line[1].color = sf::Color::Yellow;
    slope_ = (p2.y-p1.y)/(p2.x-p1.x);
    rect_ = line.getBounds();
    notify(NEW_BULLET, id_);
    checked_collisions = false;
}

sf::VertexArray Bullet::get_line(void) { return line; }

void Bullet::update_logic(void) {
    if (!checked_collisions) {
        find_potential_collisions();
    }
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
    //For every point along line:
    //check collision with collision_list
    //trim bullet to stop at first collision
    //return entity when collision is found
}
