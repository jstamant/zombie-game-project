#ifndef _DEFINES_H_
#define _DEFINES_H_

#define WINDOW_CAPTION "Zombie Game Project 2022"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define SPEED   3
#define Z_SPEED 1

#define BULLET_FLASH_DURATION 5
#define BULLET_RANGE 1000

enum Event
{
  EVENT_BULLET_FIRED,
  EVENT_ENEMY_CREATED
    /* MOVE_UP, */
    /* MOVE_DOWN, */
    /* MOVE_LEFT, */
    /* MOVE_RIGHT, */
    /* NEW_BULLET, */
    /* NEW_ENTITY, */
    /* KILL_ENTITY */
};

/* List of entities sorted by their row on the spritesheet.
 */
enum EntityRow
{
    SPRITESHEET_ROW_CHARACTER = 1,
    SPRITESHEET_ROW_ZOMBIE,
    SPRITESHEET_ROW_WALL,
    SPRITESHEET_ROW_AMMO
};

#endif //_DEFINES_H_
