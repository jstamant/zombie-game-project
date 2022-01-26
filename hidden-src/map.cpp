//************************************************
// map.cpp
//************************************************

//Include dependencies
#include "entitymanager.h"
#include <iostream>
#include "map.h"
#include <string>
#include "tile.h"
#include <tinyxml2.h>

Map::Map(const char* file, EntityManager* entitymanager) {
    //Initialize map properties
    map_width_   = 0;
    map_height_  = 0;
    tile_width_  = 0;
    tile_height_ = 0;
    //Initialize tileset properties
    tileset_.rows    = 0;
    tileset_.columns = 0;
    tileset_.loaded  = false;
    tileset_.element = NULL;
    //Initialize services
    entitymanager_ = entitymanager;
    //Load map file
    if ( doc_.LoadFile(file) )
        std::cout << "Could not load map file \"" << file << "\"\n";
    root_  = doc_.RootElement();
    map_width_   = root_->IntAttribute("width");
    map_height_  = root_->IntAttribute("height");
    tile_width_  = root_->IntAttribute("tilewidth");
    tile_height_ = root_->IntAttribute("tileheight");
    for (point_ = root_->FirstChildElement(); point_ != NULL; point_ = point_->NextSiblingElement()) {
        std::string node_name = point_->Name();
        std::string attribute_name = point_->Attribute("name");
        if ( node_name == "tileset" && !tileset_.loaded)
            load_tileset(point_);
        if ( node_name == "layer" && attribute_name == "background" )
            background_layer_ = point_;
        if ( node_name == "objectgroup" && attribute_name == "entities" )
            object_layer_ = point_;
    }
    generate_background();
}

void Map::load_tileset(tinyxml2::XMLElement* element) {
    tileset_.tiles   = element->IntAttribute("tilecount");
    tileset_.columns = element->IntAttribute("columns");
    tileset_.rows    = tileset_.tiles / tileset_.columns;
    tileset_.loaded  = true;
    tileset_.element = element;
}

/* TODO make this more general-purpose. like generate_layer() as opposed to
 * generate_background()
 */
void Map::generate_background(void) {
    int type = 0;
    //Set iterator to the first tile of the layer
    tinyxml2::XMLElement* point = background_layer_->FirstChildElement()->FirstChildElement();
    //Generate every tile from the map file
    for (int y = 0; y < map_height_; y++) {
        for (int x = 0; x < map_width_; x++) {
            type = point->IntAttribute("gid");
            entitymanager_->new_tile(new Tile(x*tile_width_, y*tile_height_, type));
            point = point->NextSiblingElement();
        }
    }
}

