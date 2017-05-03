#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_
//******************************************************************************
// messagebus.h
//******************************************************************************

//Forward declarations
class CollisionManager;
class EntityManager;
class Message;
class System;

//Include SFML dependencies
//#include <SFML/Graphics.hpp>

//Include std dependencies
#include <deque>
#include <list>

//Include dependencies

//Typedefs
typedef std::deque<Message*> Bus;
typedef std::list<System*> SystemList;

class MessageBus
{
    public:
        MessageBus();
        //Access functions
        void pushMessage(Message*);
        void registerSystem(System*);
    private:
        //Member variables
        Bus bus_;
        //System references
        SystemList        systems_;
        CollisionManager* collisionManager_;
        EntityManager*    entityManager_;
        //Functions
        void processMessage(void);
};

#endif //_MESSAGEBUS_H_

