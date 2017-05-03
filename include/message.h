#ifndef _MESSAGE_H_
#define _MESSAGE_H_
//******************************************************************************
// message.h
//******************************************************************************

//Include SFML dependencies
//#include <SFML/Graphics.hpp>

//Include std dependencies

//Include dependencies
#include "entity.h"

enum MessageType
{
    //CollisionManager messages
    CHECK_BULLET_COLLISION
};

struct Message
{
    MessageType type;
    Entity* entity;
};

#endif //_MESSAGE_H_

