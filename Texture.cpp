//
//  Texture.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/17/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Texture.hpp"
/*
    example;
    sprite[2][4][2];
    sprite[move][up].0;
    sprite[atk][down].1;
 
    example;
    tile[topLeft]
*/

Texture::Texture(unsigned int inX, unsigned int inY,
                 unsigned int inWidth, unsigned int inHeight){
    rect.x = inX;
    rect.y = inY;
    rect.w = inWidth;
    rect.h = inHeight;
}
Texture::~Texture(){
    
}
SDL_Rect Texture::getRect(){
    return rect;
}

Tile::Tile(Texture* inTexture, unsigned int inID, std::string inName){
    texture = inTexture;
    id = inID;
    name = inName;
}
Tile::~Tile(){
    
}
SDL_Rect Tile::getTexture(){
    return texture->getRect();
}
unsigned int Tile::getID(){
    return id;
}
std::string Tile::getName(){
    return name;
}

Sprite::Sprite(Texture* inTexture, unsigned int inID, std::string inName){
    texture = inTexture;
    id = inID;
    name = inName;
}
Sprite::~Sprite(){
    
}
SDL_Rect Sprite::getTexture(){
    return texture->getRect();
}
unsigned int Sprite::getID(){
    return id;
}
std::string Sprite::getName(){
    return name;
}

Gui::Gui(Texture* inTexture, unsigned int inID, std::string inName){
    texture = inTexture;
    id = inID;
    name = inName;
}
Gui::~Gui(){
    
}
SDL_Rect Gui::getTexture(){
    return texture->getRect();
}
unsigned int Gui::getID(){
    return id;
}
std::string Gui::getName(){
    return name;
}
