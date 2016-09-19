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
        int  get_health(void);
        sf::Vector2f get_position(void);
        void move(float, float);
        sf::FloatRect get_rect(void);
        virtual bool is_bullet(void);
        virtual bool is_character(void);
        virtual bool is_collidable(void);
        virtual bool is_enemy(void);
        virtual bool is_pickup(void);
        virtual bool is_solid(void);
        virtual void update_logic(void) = 0;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
        void take_damage(int);

        //Added by Joel
        void set_sprite();
        //

    protected:
        //Added by Joel
        sf::Texture texture; //Except this
        int spriteOriginX;
        int spriteOriginY;
        int spriteWidth;
        int spriteHeight;
        float orientation; //In radians
        //


        sf::Sprite sprite_;
        float x_;
        float y_;
        int id_;
        int m_health;
        sf::FloatRect m_intersect_rect;
        sf::FloatRect rect_;
        sf::RenderWindow* window_;
        sf::Mouse* mouse_;
        EntityManager* entitymanager_;
};

#endif
