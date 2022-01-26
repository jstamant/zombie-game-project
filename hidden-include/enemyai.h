#ifndef _ENEMYAI_H_
#define _ENEMYAI_H_
//************************************************
// enemyai.h
//************************************************

//Include SDL dependencies
//#include <SDL2/SDL.h>

//Include dependencies
#include "character.h"
#include "enemy.h"

class EnemyAI
{
public:
    EnemyAI(Character*);
    void setCharacter(Character*);
    void update(void);
private:
    Character* character_;
};

#endif //_ENEMYAI_H_
