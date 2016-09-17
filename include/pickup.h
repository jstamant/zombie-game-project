#ifndef _PICKUP_H
#define _PICKUP_H
//************************************************
// pickup.h
//************************************************

//Include dependencies
#include "entity.h"

class Pickup: public Entity
{
    public:
        Pickup();
        Pickup(int, int);
        virtual void update_logic(void);
        virtual bool is_pickup(void);
    private:
        int type;
};

#endif //_PICKUP_H_

