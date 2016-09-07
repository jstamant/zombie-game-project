//Include dependencies
#include "defines.h"
#include "drawable.h"
#include "subject.h"
#include <list>

//DEBUG
#include <iostream>

void Subject::add_observer(Observer* observer) {
    observers.push_back(observer);
}

void Subject::remove_observer(Observer* observer) {

}

void Subject::notify(Event event) {
    //(observers.front())->on_notify(event);
    for (std::list<Observer*>::iterator it=observers.begin(); it!=observers.end(); it++) {
        std::cout << "Notify...\n"; //DEBUG
        std::cout << "Event " << event << std::endl; //DEBUG
        (*it)->on_notify(event);
        std::cout << "Done notify!\n"; //DEBUG
    }
}

