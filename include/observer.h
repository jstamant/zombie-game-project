#ifndef _OBSERVER_H
#define _OBSERVER_H

class Observer
{
    public:
        //Lines from http://gameprogrammingpatterns.com/
        //~Observer() {}
        //virtual void on_notify(const Entity& entity, Event event) = 0;
        virtual void on_notify(const Drawable& entity, int event) = 0;
};

#endif

