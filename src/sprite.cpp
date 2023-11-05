//******************************************************************************
// sprite.cpp
//******************************************************************************

#include <iostream>

// Include SDL dependencies
#include <SDL2/SDL.h>

// Include dependencies
#include "sprite.h"

Sprite::Sprite() {
  // Centered for a 32x32 pixel sprite by default
  offset.x = 16;
  offset.y = 16;
  // Default sprite is the player sprite
  row_ = 0;
  frame_ = 0;
  // Default clip is a 32x32 pixel sprite
  rect.x = 0;
  rect.y = 0;
  rect.w = 32;
  rect.h = 32;
}

void Sprite::setRow(int new_row) {
  row_ = new_row;
  rect.y = row_ * 32;
}

void Sprite::setFrame(int frame) {
  frame_ = frame;
  rect.x = 32 * frame_;
}
