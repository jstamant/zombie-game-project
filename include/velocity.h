#ifndef _VELOCITY_H_
#define _VELOCITY_H_

/* Component for entities that defines a velocity vector in terms of magnitude
   and angle (in radians)
 */
class Velocity {
public:
  Velocity();
  void add(float, double);
  void add_components(float, float);
  void reset(void);
  float get_x(void);
  float get_y(void);
  double get_angle(void);
private:
  float x_, y_;
  void set(float, float);
};

#endif //_VELOCITY_H_
