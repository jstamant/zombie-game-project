#ifndef _SUBJECT_H
#define _SUBJECT_H
//************************************************
// subject.h
//************************************************

//Forward declarations
class Observer;

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
    protected:
        void notify(Event, int=0);
};

#endif

