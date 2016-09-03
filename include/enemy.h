#ifndef _ENEMY_H
#define _ENEMY_H

//Include dependencies
#include "character.h"
#include "subject.h"

class Enemy: public Drawable, public Subject
{
    public:
        Enemy(Observer*);
        void seek_player(void);
        static Character* p_character_ref;
};

#endif

