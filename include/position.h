#ifndef _POSITION_H_
#define _POSITION_H_

/* Component for entities that defines an x and y coordinate, and a rotation.
 */
class Position
{
 public:
    float x, y;
    double rotation;
    struct Next {
      float x;
      float y;
      double rotation;
    } next;
    void swap(void);
};

#endif //_POSITION_H_
