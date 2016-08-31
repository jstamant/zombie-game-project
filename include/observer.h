#ifndef _OBSERVER_H
#define _OBSERVER_H

//Include dependencies
#include "defines.h"
#include "drawable.h"

//This class could greatly benefit from templating
class Observer
{
    public:
        virtual void on_notify(Drawable& drawable, Event event) = 0;
    private:
};

#endif

