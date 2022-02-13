//******************************************************************************
// sprite.cpp
//******************************************************************************

//Include SDL dependencies
#include <SDL2/SDL.h>

//Include dependencies
#include "functions.h"
#include <iostream>
#include "sprite.h"

//Define static members. Required, as they are 'incomplete types' until defined.
SDL_Texture* Sprite::spritesheet = NULL;

Sprite::Sprite() {
    //Centered for a 32x32 pixel sprite by default
    offsetX = 16;
    offsetY = 16;
    //Default sprite is the player sprite
    row_ = 0;
    frame_ = 1;
    //Default clip is a 32x32 pixel sprite
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;
    //Load spritesheet if not already done
    if (spritesheet == NULL) {
        spritesheet = loadTexture("spritesheet.png");
        std::cout << "Loaded spritesheet for an entity" << std::endl;
        if (spritesheet == NULL) //Not sure if this works as intended
            std::cout << "Failed to load spritesheet" << std::endl;
    }
    //NEED TO FREE THIS TEXTURE ON DESTRUCTION
}

//******************************************************************************
// Access functions
//******************************************************************************

void Sprite::setRow(int new_row) {
    row_ = new_row;
    rect.y = row_*32;
}
