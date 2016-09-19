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
    spriteOriginX = 33*(rand()%2);
    spriteOriginY = 33;
    spriteWidth = 32;
    spriteHeight = 32;
    set_sprite();

    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
    m_health = 100;
}

Enemy::Enemy(int x, int y): Enemy::Enemy() {
    set_position(x, y);
}

/* Steps the enemy directly towards the character.
 */
void Enemy::seek_player(void) {
    float character_x = g_character->get_x();
    float character_y = g_character->get_y();
    float dx = character_x - x_;
    float dy = character_y - y_;

    angle_ = atan2(dy, dx);
    float move_x = Z_SPEED*cos(angle_);
    float move_y = Z_SPEED*sin(angle_);
    sprite_.setRotation(angle_*180/M_PI);

    //Perform movement
    move(move_x, move_y);
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
                //Adjust entity position depending on side of entry
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

bool Enemy::is_collidable(void) { return true; }
bool Enemy::is_enemy(void)      { return true; }

