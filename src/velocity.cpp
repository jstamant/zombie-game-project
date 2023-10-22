//******************************************************************************
// velocity.cpp
//******************************************************************************

#include <cmath>
#include "velocity.h"

// DEBUG
#include <iostream>

Velocity::Velocity() {
  set(0, 0);
}

/* Takes a vector, in magnitude and radians, and adds it to the stored vector.
   Adding a negative value DOES work as adding in the opposite direction of
   angle. */
void Velocity::add(float magnitude, double angle) {
  x_ += magnitude * cos(angle);
  y_ += magnitude * sin(angle);
}

/* Adds a vector, expressed in x/y components, to this velocity. */
void Velocity::add_components(float dx, float dy) {
  x_ += dx;
  y_ += dy;
}

/* Resets the vector to zero velocity. For use at the end of a tick. */
void Velocity::reset(void) {
  set(0, 0);
}

float Velocity::get_x(void) {
  // return magnitude_ * cos(angle_);
  return x_;
}

float Velocity::get_y(void) {
  // return magnitude_ * sin(angle_);
  return y_;
}

double Velocity::get_angle(void) {
  return atan2(y_, x_);
}

/* Overwrites the stored vector's values. */
void Velocity::set(float x, float y) {
  x_ = x;
  y_ = y;
}
