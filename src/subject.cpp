//************************************************
// subject.cpp
//************************************************

//Include dependencies
#include "defines.h"
#include "entity.h"
#include "subject.h"
#include <list>

void Subject::add_observer(Observer* observer) {
    observers.push_back(observer);
}

void Subject::remove_observer(Observer* observer) {

}

void Subject::notify(Event event, int id) {
    for (std::list<Observer*>::iterator it=observers.begin(); it!=observers.end(); it++) {
        (*it)->on_notify(event, id);
    }
}

