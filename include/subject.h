#ifndef _SUBJECT_H
#define _SUBJECT_H

//Include dependencies
#include "observer.h"
#include <vector>

class Subject
{
    public:
        void add_observer(Observer*);
        void remove_observer(Observer*);
    private:
        //Code from the page:
        //Observer* observers[MAX_OBSERVERS];
        //My take:
        std::vector<Observer> observers();
        int num_observers;
        //This might need to be protected:
        //void notify(const Entity& entity, Event event);
        void notify(Drawable&, int);
};

#endif

