#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
//************************************************
// userinterface.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"


/* The UserInterface class is a dynamic container for all UI elements.
 * i.e. health bars, ammo counters, mini-maps, stats, etc.
 */
class UserInterface: public Entity
{
    public:
        UserInterface();
        virtual void update_logic(void);
    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
        int m_ammo;
        int m_health;
        sf::Font m_font;
        sf::Text m_ammo_text;
        sf::Text m_health_text;
};

#endif //_USERINTERFACE_H_

