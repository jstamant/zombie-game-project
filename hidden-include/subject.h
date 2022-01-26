#ifndef _SUBJECT_H
#define _SUBJECT_H
//************************************************
// subject.h
//************************************************

//Forward declarations
class Entity;
class Observer;

//Include dependencies
#include "defines.h"
#include <list>

class Subject
{
    public:
        void addObserver(Observer*);
        void removeObserver(Observer*);
    private:
        std::list<Observer*> observers_;
    protected:
        void notify(Event, Entity*);
};

#endif

