#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

//Include dependencies
#include "character.h"
#include "defines.h"
#include "observer.h"
#include <vector>

class EntityManager : public Observer
{
    public:
        void on_notify(Drawable&, Event);
    private:
        std::vector<Character*> character_list;
};

#endif

