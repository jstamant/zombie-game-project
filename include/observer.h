#ifndef _OBSERVER_H
#define _OBSERVER_H
//************************************************
// observer.h
//************************************************

//Forward declarations
class Entity;

//Include dependencies
#include "defines.h"

class Observer
{
    public:
        virtual void onNotify(Event event, Entity* id) = 0;
    private:
};

#endif

