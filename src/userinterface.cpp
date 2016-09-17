//************************************************
// userinterface.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "character.h"
#include <string>
#include "userinterface.h"

//TODO remove this global when it's phased out properly
extern Character* g_character;

UserInterface::UserInterface() {
    m_ammo = 0;
    m_ammo_font.loadFromFile("arial.ttf");
    m_ammo_text.setString("NO STRING");
    m_ammo_text.setCharacterSize(24);
    m_ammo_text.setFillColor(sf::Color::Black);
    m_ammo_text.setFont(m_ammo_font);
}

/* Override the default implementation from class Entity, in order to draw the
 * UI's set of drawables.
 */
void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_ammo_text);
}

void UserInterface::update_logic(void) {
    //Set ammo to the player's ammo
    m_ammo = g_character->get_ammo();
    m_ammo_text.setString(std::to_string(m_ammo));
    //Set health bar to player's health
}

