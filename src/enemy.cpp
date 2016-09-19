//************************************************
// enemy.cpp
//************************************************

//Include dependencies
#include "character.h"
#include "enemy.h"
#include "entity.h"
#include "entitymanager.h"
#include <math.h>

//DEBUG
#include <iostream>

//TODO remove this once the global is phased out
extern Character* g_character;

Enemy::Enemy() {
    sf::Image image;
    image.loadFromFile("enemy.png");
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite_.setTexture(texture);
    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
    m_health = 100;
}

Enemy::Enemy(int x, int y): Enemy::Enemy() {
    set_position(x, y);
}

/* Steps the enemy directly towards the character.
 * TODO This could potentially benefit from vector math.
 */
void Enemy::seek_player(void) {
    float character_x = g_character->get_x();
    float character_y = g_character->get_y();
    float dx = character_x - x_;
    float dy = character_y - y_;

    float angle;
    angle = atan2(dy, dx);
    float move_x = Z_SPEED*cos(angle);
    float move_y = Z_SPEED*sin(angle);
    sprite_.setRotation(angle*180/M_PI);

    //Perform movement
    move(move_x, move_y);
    rect_ = sprite_.getGlobalBounds();
}

void Enemy::update_logic(void) {
    seek_player();
    if (m_health <= 0) {
        entitymanager_->del_entity(id_);
    }
    collision_list = entitymanager_->check_collisions(rect_);
    if ( !collision_list.empty() ) {
        for (std::list<Entity*>::iterator it=collision_list.begin(); it!=collision_list.end(); it++) {
            if ( (*it)->get_id() != id_ ) {
                //move_away_from(*it);
                if ( (*it)->is_character() ) {
                    (*it)->take_damage(1);
                }
            }
        }
        collision_list.clear();
    }
    //Check for collisions with solids
    collision_list = entitymanager_->check_collisions(rect_);
    if ( !collision_list.empty() ) {
        for (std::list<Entity*>::iterator it=collision_list.begin(); it!=collision_list.end(); it++) {
            if ( (*it)->is_solid() ) {
                sf::FloatRect solid_rect = (*it)->get_rect();
                rect_.intersects(solid_rect, m_intersect_rect);
                //Adjust character position depending on side of entry
                if ( m_intersect_rect.width < m_intersect_rect.height) {
                    if ( rect_.left < solid_rect.left ) {
                        move(-m_intersect_rect.width, 0);
                    }else{
                        move(m_intersect_rect.width, 0);
                    }
                }else{
                    if ( rect_.top < solid_rect.top ) {
                        move(0, -m_intersect_rect.height);
                    }else{
                        move(0, m_intersect_rect.height);
                    }
                }
            }
        }
        collision_list.clear();
    }
}

/* Slightly moves the enemy away from a colliding entity.
 * @param Entity in collision with the enemy.
 */
/*void Enemy::move_away_from(Entity* entity) {
    sf::Vector2f entity_position = entity->get_position();
    sf::Vector2f position(x_, y_);
    sf::Vector2f distance_vector = entity_position - position;
    float angle = atan2(distance_vector.y, distance_vector.x) * 180 / PI;
    //float distance = sqrt(pow(distance_vector.x,2)+pow(distance_vector.y,2));
    float move_x = -0.5*cos(angle);
    float move_y = -0.5*sin(angle);
    move(move_x, move_y);
}
*/

bool Enemy::is_collidable(void) { return true; }
bool Enemy::is_enemy(void)      { return true; }

