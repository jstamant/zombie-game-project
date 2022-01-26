#ifndef _ENEMY_H_
#define _ENEMY_H_
//************************************************
// enemy.h
//************************************************

//Include dependencies
#include "character.h"
#include "entity.h"
//#include <list>

class Enemy: public Entity
{
public:
    Enemy();
    Enemy(int, int);
    //Access functions
    void setTarget(Character*);
    void updateLogic(void);
    //virtual bool is_collidable(void);
    //virtual bool is_enemy(void);
    void seekPlayer();
private:
    //std::list<Entity*> collision_list;
    Character* target_;
};

#endif //_ENEMY_H_

