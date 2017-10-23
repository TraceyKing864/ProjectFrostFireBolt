//
//  TextureManager.hpp
//  Frost Insignia
//
//  Created by Tracey King on 4/10/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <list>

#include "Texture.hpp"

const int TILEMAP = 0;
const int SPRITEMAP = 1;
const int GUIMAP = 2;

//this is how texture properties are determined
class TextureManager{
private:
    const unsigned int tile_width = 24;
    const unsigned int tile_height = 24;
    const unsigned int sprite_width = 24;
    const unsigned int sprite_height = 24;
    const unsigned int gui_width = 24;
    const unsigned int gui_height = 24;
    const unsigned int action_width = 24;
    const unsigned int action_height = 36;
    
    static TextureManager* static_instance;
    std::vector<std::vector<Texture>> spriteTextures;
    std::vector<std::vector<Texture>> tileTextures;
    std::vector<std::vector<Texture>> guiTextures;
    std::vector<Sprite> sprites;
    std::vector<Tile> tiles;
    std::vector<Gui> gui;
    
    TextureManager();
    ~TextureManager();
public:
    static TextureManager* instance();
    Sprite* getSprite(unsigned int inSpriteID);
    Tile* getTile(unsigned int inTileID);
    Gui* getGui(unsigned int inGuiID);
};

//TextureManager* TextureManager::static_instance = NULL;

#endif /* TextureManager_hpp */
