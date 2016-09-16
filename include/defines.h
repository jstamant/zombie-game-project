#ifndef _DEFINES_H
#define _DEFINES_H

#define WINDOW_CAPTION "Zombie Game Project"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define FRAMELIMIT 60

#define MAX_ENTITIES 20

#define SPEED   3
#define Z_SPEED 1

#define PI 3.14159265 //TEMP, THIS SHOULD BE ELSEWHERE??? LIKE IN A LIBRARY?

#define BULLET_FLASH_DURATION 5
#define BULLET_RANGE 200

#define MAX_OBSERVERS 2

enum Event
{
    SHOOT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    NEW_BULLET
};

#endif

