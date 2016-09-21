//************************************************
// subject.cpp
//************************************************

//Include dependencies
#include "defines.h"
#include "entity.h"
#include "observer.h"
#include "subject.h"
#include <list>

void Subject::addObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {

}

void Subject::notify(Event event, Entity* entity) {
    for (std::list<Observer*>::iterator it=observers_.begin(); it!=observers_.end(); it++) {
        (*it)->onNotify(event, entity);
    }
}

