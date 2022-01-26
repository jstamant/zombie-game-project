#ifndef _COMMAND_H
#define _COMMAND_H

//Include dependencies
#include "character.h"

class Command
{
    public:
        //~Command() {}
        //virtual void execute() = 0;
        virtual void execute(Character& character) = 0;
};

//Define all assignable commands
class KeyW : public Command
{
    public:
        virtual void execute(Character& character) { character.move_up(); }
};

class KeyA : public Command
{
    public:
        virtual void execute(Character& character) { character.move_left(); }
};

class KeyS : public Command
{
    public:
        virtual void execute(Character& character) { character.move_down(); }
};

class KeyD : public Command
{
    public:
        virtual void execute(Character& character) { character.move_right(); }
};

class MouseMovement : public Command
{
    public:
        virtual void execute(Character& character) {
            character.rotate();
        }
};

#endif
