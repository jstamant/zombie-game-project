#ifndef _TILE_H
#define _TILE_H
//************************************************
// tile.h
//************************************************

//Include dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "entity.h"

/* Class for all drawable background tiles.
 */
class Tile: public Entity
{
    public:
        Tile();
        Tile(int, int, int);
        //Access functions
        //General-purpose functions
        void set_tile(int);
        sf::Vector2i retrieve_texture_coord(int);
        //Update functions
        virtual void update_logic(void);
    private:
        ;
};

#endif //_TILE_H

