#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_
//************************************************
// collisionmanager.h
//************************************************

//Forward declarations
class Entity;

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include std dependencies
#include <list>
#include <unordered_map>

//Include dependencies
#include "defines.h"
#include "observer.h"
#include "system.h"

//Typedefs
typedef std::list<Entity*>                EntityList;
typedef std::unordered_map<ID,Entity*>    EntityMap;
typedef std::pair<ID,Entity*>             EntityPair;
typedef std::unordered_map<ID,EntityList> CollisionList;

/* Class that calculates collisions, and keeps record of all entity hitboxes.
 */
class CollisionManager: public System, public Observer
{
    public:
        CollisionManager();
        //Communication functions
        virtual void onNotify(Event, Entity*);
        //Access functions
        void deregisterEntity(Entity*);
        void registerEntity(Entity*);
        //General-purpose functions
        EntityList checkCollisions(Entity*);
        //Discreet collision functions
        void bulletCollision(Entity*);
        //Update functions
        void checkAllCollisions(void);
        void processCollisions(void);
        //void pushAllCollisions(void);
    private:
        //Member variables
        //RectMap       mobileRects_;
        //RectMap       entityRects_;
        EntityMap     mobiles_;
        EntityMap     entities_;
        EntityMap     discreet_;
        CollisionList entityCollisionsList_;
};

#endif //_COLLISIONMANAGER_H_

