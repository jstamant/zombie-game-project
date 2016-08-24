//enemy.h

//TODO ADD A HEADER GUARD

#include "character.h"

class Enemy: public Drawable
{
    public:
        Enemy();
        void seek_player(Character*);
};

