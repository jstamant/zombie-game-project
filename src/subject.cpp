//Include dependencies
#include "drawable.h"
#include "subject.h"
#include <vector>

void Subject::add_observer(Observer* observer) {
    observers.push_back(observer);
}

void Subject::remove_observer(Observer* observer) {

}

void notify(Drawable& drawable, int event) {

}

