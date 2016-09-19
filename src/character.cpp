//************************************************
// character.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "character.h"
#include "defines.h"
#include "entity.h"
#include "entitymanager.h"
#include <math.h>

//DEBUG
#include <iostream>

Character::Character(){
    spriteOriginX = 0;
    spriteOriginY = 0;
    spriteWidth = 32;
    spriteHeight = 32;
    set_sprite();

    sprite_.setOrigin(16, 16);
    rect_ = sprite_.getGlobalBounds();
    m_ammo = 100;
    m_health = 100;
}

Character::Character(int x, int y): Character::Character() {
    set_position(x, y);
}

float  Character::get_x(void)     { return sprite_.getPosition().x; }
float  Character::get_y(void)     { return sprite_.getPosition().y; }
double Character::get_angle(void) { return angle; }

void Character::move_up(void) {
    y_ -= SPEED;
    set_position(x_, y_);
}

void Character::move_down(void) {
    y_ += SPEED;
    set_position(x_, y_);
}

void Character::move_left(void) {
    x_ -= SPEED;
    set_position(x_, y_);
}

void Character::move_right(void) {
    x_ += SPEED;
    set_position(x_, y_);
}

/* Rotates the character to face the mouse pointer.
 */
void Character::rotate(void) {
    sf::Vector2i mouse_vector(mouse_->getPosition(*window_));
    sf::Vector2i sprite_vector(sprite_.getPosition());
    sf::Vector2i angle_vector(mouse_vector - sprite_vector);
    angle_ = atan2(angle_vector.y, angle_vector.x) * 180 / M_PI;
    sprite_.setRotation(angle_);
}

/* Generates a bullet, and passes it to the entity manager for tracking.
 */
void Character::shoot(void) {
    if (m_ammo > 0)
    {
        sf::Vector2f mouse_position(mouse_->getPosition(*window_));
        Bullet* bullet = new Bullet(sprite_.getPosition(), mouse_position);
        entitymanager_->new_entity(bullet);
        m_ammo--;
    }
}

void Character::update_logic(void)
{
    if (mouse_ && window_) {
        rotate();
    }
    if (m_health <= 0) {
        entitymanager_->del_entity(id_);
    }
    //Check for collisions with pickups
    m_collision_list = entitymanager_->check_collisions_pickups(rect_);
    if ( !m_collision_list.empty() ) {
        for (std::list<Entity*>::iterator it=m_collision_list.begin(); it!=m_collision_list.end(); it++) {
            m_ammo += 10;
            entitymanager_->del_entity((*it)->get_id());
        }
        m_collision_list.clear();
    }
    //Check for collisions with solids
    m_collision_list = entitymanager_->check_collisions(rect_);
    if ( !m_collision_list.empty() ) {
        for (std::list<Entity*>::iterator it=m_collision_list.begin(); it!=m_collision_list.end(); it++) {
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
        m_collision_list.clear();
    }
}

bool Character::is_character(void) { return true; }
bool Character::is_collidable(void) { return true; }

int Character::get_ammo(void) { return m_ammo; }
