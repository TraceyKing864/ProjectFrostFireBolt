//
//  TextureManager.cpp
//  Frost Insignia
//
//  Created by Tracey King on 4/10/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "TextureManager.hpp"

TextureManager* TextureManager::static_instance = NULL;

TextureManager::TextureManager(){
    ////////////////////////////////
    //tile information            //
    ////////////////////////////////
    
    //current tileMap size
    int width = 1366 / tile_width;
    int height = 1007 / tile_width;
    
    int inX = 0;
    int inY = 0;
    for(int j = 0; j < height; j++){
        std::vector<Texture> temp;
        for(int i = 0; i < width; i++){
            temp.push_back(Texture(inX, inY, tile_width, tile_height));
            inX += tile_width;
        }
        tileTextures.push_back(temp);
        temp.clear();
        inY += tile_height;
        inX = 0;
    }
    tiles.push_back(Tile(&tileTextures[16][30], 0, "grass"));
    tiles.push_back(Tile(&tileTextures[18][30], 1, "dirt"));
    tiles.push_back(Tile(&tileTextures[20][30], 2, "sand?"));
    tiles.push_back(Tile(&tileTextures[22][30], 3, "idk"));
    
    //tileID = Grass (792, 312)
    //tileID = Dirt (792, 264)
    //tileID = Sand (792, 288)
    //tileID = Water (120, 744)
    ////////////////////////////////
    //sprite information          //
    ////////////////////////////////
    
    //current spriteMap size
    width = 480 / sprite_width;
    height = 648 / sprite_height;
    
    inX = 0;
    inY = 0;
    for(int j = 0; j < height; j++){
        std::vector<Texture> temp;
        for(int i = 0; i < width; i++){
            temp.push_back(Texture(inX, inY, sprite_width, sprite_height));
            inX += sprite_width;
        }
        spriteTextures.push_back(temp);
        temp.clear();
        inY += sprite_height;
        inX = 0;
    }
    sprites.push_back(Sprite(&spriteTextures[1][1], 0, "warrior"));
    sprites.push_back(Sprite(&spriteTextures[1][2], 1, "rogue"));
    sprites.push_back(Sprite(&spriteTextures[1][3], 2, "archer"));
    sprites.push_back(Sprite(&spriteTextures[1][4], 3, "mage"));
    //spriteID = Warrior (1, 1)
    //spriteID = Thief (2, 1)
    //spriteID = Archer (3, 1)
    //spriteID = Mage (4, 1)
    
    ////////////////////////////////
    //Gui information       //
    ////////////////////////////////
    //current spriteMap size
    width = 240 / gui_width;
    height = 480 / gui_height;
    
    inX = 0;
    inY = 0;
    for(int j = 0; j < height; j++){
        std::vector<Texture> temp;
        for(int i = 0; i < width; i++){
            temp.push_back(Texture(inX, inY, gui_width, gui_height));
            inX += gui_width;
        }
        guiTextures.push_back(temp);
        temp.clear();
        inY += gui_height;
        inX = 0;
    }
    gui.push_back(Gui(&guiTextures[0][0], 0, "cursor_white_0"));
    gui.push_back(Gui(&guiTextures[1][0], 1, "cursor_white_1"));
    gui.push_back(Gui(&guiTextures[2][0], 2, "cursor_blue_0"));
    gui.push_back(Gui(&guiTextures[3][0], 3, "cursor_blue_1"));
    gui.push_back(Gui(&guiTextures[4][0], 4, "cursor_red_0"));
    gui.push_back(Gui(&guiTextures[6][0], 5, "cursor_yellow_0"));
    
    gui.push_back(Gui(&guiTextures[10][3], 6, "textbox_up_left"));
    gui.push_back(Gui(&guiTextures[10][4], 7, "textbox_up"));
    gui.push_back(Gui(&guiTextures[10][5], 8, "textbox_up_right"));
    gui.push_back(Gui(&guiTextures[11][3], 9, "textbox_left"));
    gui.push_back(Gui(&guiTextures[11][4], 10, "textbox_middle"));
    gui.push_back(Gui(&guiTextures[11][5], 11, "textbox_right"));
    gui.push_back(Gui(&guiTextures[12][3], 12, "textbox_down_left"));
    gui.push_back(Gui(&guiTextures[12][4], 13, "textbox_down"));
    gui.push_back(Gui(&guiTextures[12][5], 14, "textbox_down_right"));
    
    gui.push_back(Gui(&guiTextures[10][6], 15, "ally_marker"));
    gui.push_back(Gui(&guiTextures[10][7], 16, "enemy_marker"));
    
    gui.push_back(Gui((new Texture(0, 312, action_width, action_height)), 17, "ability_cursor"));
    gui.push_back(Gui((new Texture(24, 312, action_width, action_height)), 18, "ability_blank"));
    gui.push_back(Gui((new Texture(48, 312, action_width, action_height)), 19, "ability_defend"));
    gui.push_back(Gui((new Texture(72, 312, action_width, action_height)), 20, "ability_attack"));
    
}
TextureManager::~TextureManager(){
    tiles.clear();
    sprites.clear();
    gui.clear();
    tileTextures.clear();
    spriteTextures.clear();
    guiTextures.clear();
}
TextureManager* TextureManager::instance(){
    if(!static_instance)
        static_instance = new TextureManager();
    return static_instance;
}
Sprite* TextureManager::getSprite(unsigned int inSpriteID){
    return &(sprites[inSpriteID]);
}
Tile* TextureManager::getTile(unsigned int inTileID){
    return &(tiles[inTileID]);
}
Gui* TextureManager::getGui(unsigned int inGuiID){
    return &(gui[inGuiID]);
}
