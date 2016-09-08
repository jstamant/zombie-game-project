#ifndef _ENEMY_H
#define _ENEMY_H

//Include dependencies
#include "entity.h"
#include "character.h"

class Enemy: public Entity
{
    public:
        Enemy();
        void seek_player(void);
        static Character* p_character_ref;
};

#endif

