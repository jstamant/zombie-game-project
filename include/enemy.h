#ifndef _ENEMY_H
#define _ENEMY_H

//Include dependencies
#include "entity.h"

class Enemy: public Entity
{
    public:
        Enemy();
        virtual void update_logic(void);
        virtual bool is_collidable(void);
        virtual bool is_enemy(void);
    private:
        void seek_player(void);
};

#endif

