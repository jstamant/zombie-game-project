//************************************************
// tile.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "tile.h"

//DEBUG
#include <iostream>

Tile::Tile() {
    //sf::Image image;
    //image.loadFromFile("tileset.png");
    //texture_.loadFromImage(image); //Needs optimizing...
    //sprite_.setTexture(texture_);
    //set_tile(0);
    rect_ = sprite_.getGlobalBounds();
}

Tile::Tile(int x, int y, int gid): Tile() {
    set_position(x, y);
    set_tile(gid);
}

//************************************************
// Access functions
//************************************************

// None


//************************************************
// General-purpose functions
//************************************************

/* Sets the tile's texture to the given tile number on the spritesheet.
 * @param gid Tile number on the spritesheet.
 */
void Tile::set_tile(int gid) {
    sf::Vector2i texture_position = retrieve_texture_coord(gid);
    sf::IntRect  texture_rect(texture_position, sf::Vector2i(32, 32));
    sprite_.setTextureRect( texture_rect );
}

/* Returns the position of a tile on the spritesheet given the tile number.
 * TODO The tileset size is hardcoded. It needs to figure it out from either
 * Map, or somewhere else.
 * @param gid Tile number to retrieve the coordinates from.
 * @return Returns the position of the tile on the spritesheet as a vector.
 * Returns (0, 0) if the tile was not found.
 */
sf::Vector2i Tile::retrieve_texture_coord(int gid) {
    int tile_count = 1;
    sf::Vector2i texture_position(0, 0);
    for (int y=0; y<5; y++) {
        for (int x=0; x<2; x++) {
            if ( tile_count == gid )
            {
                //Decode to a position on the spritesheet
                texture_position.x = x*32 + x;
                texture_position.y = y*32 + y;
                return texture_position;
            }
            else
            {
                tile_count++;
            }
        }
    }
    return texture_position;
}

//************************************************
// Updating functions
//************************************************

void Tile::update_logic(void) { }

