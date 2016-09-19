#ifndef _MAP_H
#define _MAP_H
//************************************************
// map.h
//************************************************

//Include dependencies
#include "entitymanager.h"
#include <tinyxml2.h>

//Typedefs
typedef struct
{
    int  tiles;
    int  rows;
    int  columns;
    bool loaded;
    tinyxml2::XMLElement* element;
} Tileset;

class Map
{
    public:
        Map(const char*, EntityManager*);
    private:
        //Map properties
        int map_width_;
        int map_height_;
        int tile_width_;
        int tile_height_;
        //Tileset properties
        Tileset tileset_;
        //Services
        EntityManager* entitymanager_;
        //XML file resources and shortcuts
        tinyxml2::XMLDocument doc_;
        tinyxml2::XMLElement* root_;
        tinyxml2::XMLElement* point_;
        tinyxml2::XMLElement* background_layer_;
        tinyxml2::XMLElement* object_layer_;
        //Initialization
        void load_tileset(tinyxml2::XMLElement*);
        void generate_background(void);
};

#endif //_MAP_H

