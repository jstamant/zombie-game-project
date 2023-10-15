//******************************************************************************
// bullet.cpp
//******************************************************************************

//Include dependencies
#include "bullet.h"
#include "defines.h"
#include <SDL2/SDL.h>

Bullet::Bullet(SDL_Point p1, SDL_Point p2) {
  source.x = p1.x;
  source.y = p1.y;
  target.x = p2.x;
  target.y = p2.y;
  // TODO ttl should be moved to private
  ttl = BULLET_FLASH_DURATION;
  extendLine();
}

// //******************************************************************************
// // Access functions
// //******************************************************************************

// sf::VertexArray Bullet::get_line(void) { return line; }
// void Bullet::setEndpoint(sf::Vector2f point) { line[1].position = point; }

// void Bullet::update_logic(void) {
//     /*
//     if (!checked_collisions) {
//         //find_potential_collisions();
//         //find_first_collision();
//         collision_list = entitymanager_->collision_line(line[0].position, line[1].position);
//         if ( !collision_list.empty() ) {
//             collision_list.front()->take_damage(20);
//             line[1].position = entitymanager_->pop_collision_point();
//             collision_list.clear();
//         }
//         checked_collisions = true;
//     }
//     */
//     if (--time_to_live == 0) {
//         entitymanager_->del_entity(id_);
//     }
// }

/* A custom draw interface for the bullet, as it doesn't use a sprite.
 */
void Bullet::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, SDL_ALPHA_OPAQUE); //Yellow
    SDL_RenderDrawLine(renderer, source.x, source.y, target.x, target.y);
}

// /* Gets the entity manager to provide a list of potential collisions.
//  */
// void Bullet::find_potential_collisions(void) {
//     collision_list = entitymanager_->check_collisions(rect_);
// }

// /* Find the first collision along the bullet's path.
//  */
// void Bullet::find_first_collision(void) {
//     std::cout << "First collision:\n";
//     float dx = line[1].position.x - line[0].position.x;
//     float step_x = dx/BULLET_RANGE;
//     float dy = line[1].position.y - line[0].position.y;
//     float step_y = dy/BULLET_RANGE;
//     //For every point along line:
//     float check_x = line[0].position.x;
//     float check_y = line[0].position.y;
//     for (int i=0; i<BULLET_RANGE; i++) {
//         //Check collisions at check_x,check_y
//         for (std::list<Entity*>::iterator it=collision_list.begin(); it!=collision_list.end(); it++) {
//             if ((*it)->get_rect()->contains(check_x, check_y)) {
//                 if ( (*it)->is_character() ) {
//                     std::cout << "Character!\n";
//                     return;
//                 }
//                 if ( !(*it==this) ) {
//                     //Trim bullet
//                     //DEBUG
//                     std::cout << "HIT?\n";
//                     //DEBUG
//                     line[1].position = sf::Vector2f(check_x, check_y);
//                     return;
//                 }else{
//                     std::cout << "Bullet!\n";
//                 }
//             }
//         }

//         //Check next point in the line
//         check_x += step_x;
//         check_y += step_y;
//     }
// }

/* Extends or trims the bullet line to the global maximum bullet range. Not
 * pure. This function mutates @target.
 */
void Bullet::extendLine(void) {
    float dx = target.x - source.x;
    float dy = target.y - source.y;
    float distance = sqrt(pow(dx,2) + pow(dy,2));
    float distance_ratio = BULLET_RANGE/distance;
    float new_dx = distance_ratio*dx;
    float new_dy = distance_ratio*dy;
    target.x = source.x + new_dx;
    target.y = source.y + new_dy;
}
