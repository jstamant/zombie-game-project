//******************************************************************************
// enemyai.cpp
//******************************************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "enemyai.h"

//DEBUG
//#include <iostream>

EnemyAI::EnemyAI(Character* character) {
    setCharacter(character);
}

//******************************************************************************
// Access functions
//******************************************************************************

void EnemyAI::setCharacter(Character* target) {
    character_ = target;
}
//******************************************************************************
// Update functions
//******************************************************************************
