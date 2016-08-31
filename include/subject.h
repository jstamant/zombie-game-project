#ifndef _SUBJECT_H
#define _SUBJECT_H

//Include dependencies
#include "observer.h"
#include <vector>

class Subject
{
    public:
        std::vector<Observer*> observers;
        void add_observer(Observer*);
        void remove_observer(Observer*);
        //int num_observers;
    private:
    protected:
        void notify(Drawable&, Event);
};

#endif

