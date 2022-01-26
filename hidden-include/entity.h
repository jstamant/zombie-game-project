#ifndef _ENTITY_H_
#define _ENTITY_H_
//************************************************
// entity.h
//************************************************

//Forward declarations
//class EntityManager;

//Include SDL dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "defines.h"
#include "sprite.h"

class Entity
{
public:
    Entity();
    Entity(int, int);
    //Access functions
    // int            get_health(void);
    int            getID(void);
    SDL_FPoint     getPosition(void);
    // void           setCollisionList(std::list<ID>);
    void           setID(int);
    void           setPosition(float, float);
    // //Entity-type checking functions (deprecated?)
    // virtual bool   is_bullet(void);
    // virtual bool   is_character(void);
    // virtual bool   is_collidable(void);
    // virtual bool   is_enemy(void);
    // virtual bool   is_pickup(void);
    // virtual bool   is_solid(void);
    // //Updating functions
    void         move(float, float);
    virtual void updateLogic(void) = 0;
    // virtual void   draw(sf::RenderTarget&, sf::RenderStates) const;
    virtual void draw(void) const;
    // void           take_damage(int);   //Does this also have to be public?
    // //Setting core game resources (deprecated, to be replaced with statics)
    // void set_window(sf::RenderWindow*);
    // void set_mouse(sf::Mouse*);
    // void set_entitymanager(EntityManager*);
    // //To be sorted:
    // void kill(void);
    Sprite sprite;
    //static SDL_Texture* spritesheet; //TEMP HERE, TO BE PROTECTED
protected:
    //Intrinsic members
    float          x_;
    float          y_;
    double         angle_;
    // int            health_;
    int            id_;
    // int            origin_x_;
    // int            origin_y_;
    // std::list<ID>  collisionList_; //DEPRECATED. OUT OF THE SCOPE OF THIS CLASS
    // sf::Texture    texture_;
    // sf::FloatRect  rect_;
    // //Collision system helpers
    // //(to be removed when a REAL collision system is implemented)
    // sf::FloatRect m_intersect_rect;
    // //References to core resources
    // //(deprecated; to be replaced with static members, or a singleton-type)
    // sf::RenderWindow*   window_;
    // sf::Mouse*          mouse_;
    // EntityManager*      entitymanager_;
    // static sf::Texture* spritesheet_;
};

#endif //_ENTITY_H_
