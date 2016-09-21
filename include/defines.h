#ifndef _DEFINES_H
#define _DEFINES_H

#define WINDOW_CAPTION "Zombie Game Project 1995 1/3"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define FRAMELIMIT 60

#define MAX_ENTITIES 20

#define SPEED   3
#define Z_SPEED 1

#define BULLET_FLASH_DURATION 5
#define BULLET_RANGE 1000

#define MAX_OBSERVERS 2

#define SCALE 1

enum Event
{
    SHOOT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    NEW_BULLET,
    NEW_ENTITY,
    KILL_ENTITY
};

/* List of entities sorted by their row on the spritesheet.
 */
enum EntityRow
{
    CHARACTER = 1,
    ZOMBIE,
    WALL,
    AMMO
};

typedef int ID;

#endif

