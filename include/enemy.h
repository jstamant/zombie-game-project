#ifndef _ENEMY_H
#define _ENEMY_H
//************************************************
// enemy.h
//************************************************

//Include dependencies
#include "entity.h"
#include <list>

class Enemy: public Entity
{
    public:
        Enemy();
        Enemy(int, int);
        virtual void update_logic(void);
        virtual bool is_collidable(void);
        virtual bool is_enemy(void);
    private:
        void seek_player(void);
        //void move_away_from(Entity*);
        std::list<Entity*> collision_list;
};

#endif

