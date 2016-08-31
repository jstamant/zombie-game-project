//Include dependencies
#include "entitymanager.h"
#include <vector>

void EntityManager::on_notify(Drawable& drawable, Event event) {
    switch (event) {
        case REQUEST_CHARACTER_POSITION:
            for (int i=0; i<character_list.size(); i++) {
                //character_list[i]->notify();
            }
            break;
        default:
            break;
    }
}


