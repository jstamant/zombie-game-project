#ifndef _SUBJECT_H_
#define _SUBJECT_H_
//************************************************
// subject.h
//************************************************

// Forward declarations
class Observer;

// Include dependencies
#include "defines.h"
#include <entt/entt.hpp>
#include <list>

class Subject {
public:
  void addObserver(Observer*);
  void removeObserver(Observer*);

private:
  std::list<Observer*> observers_;

protected:
  void notify(entt::entity, Event);
};

#endif // _SUBJECT_H_
