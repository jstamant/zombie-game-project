//************************************************
// subject.cpp
//************************************************

// Include dependencies
#include "defines.h"
#include "subject.h"
#include <entt/entt.hpp>
#include "observer.h"
#include <list>

// DEBUG
#include <iostream>

void Subject::addObserver(Observer* observer) {
  observers_.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {}

void Subject::notify(entt::entity entity, Event event) {
  for (std::list<Observer *>::iterator it = observers_.begin();
       it != observers_.end(); it++) {
    (*it)->onNotify(entity, event);
  }
}
