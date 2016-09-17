#ifndef _ENTITY_H_
#define _ENTITY_H_
//************************************************
// entity.h
//************************************************

//Forward declarations
class EntityManager;

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "subject.h"

class Entity: public sf::Drawable, public Subject
{
    public:
        Entity();
        Entity(int, int);
        sf::Sprite get_sprite(void);
        void set_window(sf::RenderWindow*);
        void set_mouse(sf::Mouse*);
        void set_entitymanager(EntityManager*);
        void set_id(int);
        void set_position(float, float);
        int  get_id(void);
        void move(float, float);
        sf::FloatRect get_rect(void);
        virtual bool is_bullet(void);
        virtual bool is_character(void);
        virtual bool is_collidable(void);
        virtual bool is_enemy(void);
        virtual bool is_pickup(void);
        virtual void update_logic(void) = 0;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    protected:
        sf::Texture texture;
        sf::Sprite sprite_;
        float x_;
        float y_;
        int id_;
        sf::FloatRect rect_;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        EntityManager* entitymanager_;
};

#endif
