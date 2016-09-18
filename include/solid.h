#ifndef _SOLID_H
#define _SOLID_H
//************************************************
// solid.h
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"

class Solid: public Entity
{
    public:
        Solid();
        Solid(int, int);
        virtual void update_logic(void);
        virtual bool is_collidable(void);
        virtual bool is_solid(void);
    private:
};

#endif //_SOLID_H

