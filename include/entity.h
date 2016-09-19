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
        //Access functions
        int           get_health(void);
        int           get_id(void);
        sf::Vector2f  get_position(void);
        sf::FloatRect get_rect(void);
        sf::Sprite    get_sprite(void);
        void          set_id(int);
        void          set_position(float, float);
        //Entity-type checking functions (deprecated?)
        virtual bool  is_bullet(void);
        virtual bool  is_character(void);
        virtual bool  is_collidable(void);
        virtual bool  is_enemy(void);
        virtual bool  is_pickup(void);
        virtual bool  is_solid(void);
        //Updating functions
        void          move(float, float); //Why is this public?
        virtual void  update_logic(void) = 0;
        virtual void  draw(sf::RenderTarget&, sf::RenderStates) const;
        void          take_damage(int);   //Does this also have to be public?
        //Setting core game resources (deprecated, to be replaced with statics)
        void set_window(sf::RenderWindow*);
        void set_mouse(sf::Mouse*);
        void set_entitymanager(EntityManager*);
    protected:
        //Intrinsic members
        float         x_;
        float         y_;
        float         angle_;
        int           m_health;
        int           id_;
        int           origin_x_;
        int           origin_y_;
        sf::Texture   texture_;
        sf::Sprite    sprite_;
        sf::FloatRect rect_;
        //Sprite/texture data (deprecated)
        void set_sprite(void); //Need to rename this
        int spriteOriginX;
        int spriteOriginY;
        int spriteWidth;
        int spriteHeight;
        //Collision system helpers
        //(to be removed when a REAL collision system is implemented)
        sf::FloatRect m_intersect_rect;
        //References to core resources
        //(deprecated; to be replaced with static members, or a singleton-type)
        sf::RenderWindow*   window_;
        sf::Mouse*          mouse_;
        EntityManager*      entitymanager_;
        static sf::Texture* spritesheet_;
};

#endif

