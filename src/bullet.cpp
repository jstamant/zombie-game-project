//************************************************
// bullet.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "bullet.h"
#include "defines.h"
#include "entitymanager.h"

Bullet::Bullet(sf::Vector2f p1, sf::Vector2f p2):
    //TODO: need to figure out why I need to initialize this here...
    line(sf::Lines, 2) {
    time_to_live = BULLET_FLASH_DURATION;
    line[0].position = p1;
    line[1].position = p2;
    line[0].color = sf::Color::Yellow;
    line[1].color = sf::Color::Yellow;
}

sf::VertexArray Bullet::get_line(void) { return line; }

void Bullet::update_logic(void) {
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

