//******************************************************************************
// position.cpp
//******************************************************************************

#include "position.h"

// DEBUG
#include <iostream>

void Position::swap(void) {
  x = next.x;
  y = next.y;
  rotation = next.rotation;
}
