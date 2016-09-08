#ifndef _SUBJECT_H
#define _SUBJECT_H

//Include dependencies
#include "entity.h"
#include "observer.h"
#include <list>

class Subject
{
    public:
        void add_observer(Observer*);
        void remove_observer(Observer*);
    private:
        std::list<Observer*> observers;
        //int num_observers;
    protected:
        void notify(Event);
};

#endif

