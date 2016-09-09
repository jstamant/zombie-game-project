#ifndef _ENEMY_H
#define _ENEMY_H

//Include dependencies
#include "entity.h"
#include "character.h"

class Enemy: public Entity
{
    public:
        Enemy();
        static Character* character_;
        virtual void update_logic(void);
        virtual bool is_enemy(void);
    private:
        void seek_player(void);
};

#endif

