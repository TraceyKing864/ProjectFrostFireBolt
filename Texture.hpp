//
//  Texture.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/17/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

//each sprite ID will have
//sprites have up, down, left, right idle sprites with 2 states that alternate
//*note:walking sprite is the same as idle sprite only faster?? maybe
//sprites have up, down, left, right attacking sprites

class Texture{
private:
    //SDL_Texture* TextureMap;
    //std::string fileName;
    SDL_Rect rect;
public:
    Texture(unsigned int inX, unsigned int inY,
            unsigned int inWidth, unsigned int inHeight);
    ~Texture();
    SDL_Rect getRect();
    //SDL_Texture* getTextureMap();
};

class Tile{
private:
    unsigned int id;
    std::string name;
    Texture* texture;
public:
    Tile(Texture* inTexture, unsigned int inID, std::string inName);
    ~Tile();
    unsigned int getID();
    std::string getName();
    SDL_Rect getTexture();
};

class Sprite{
private:
    unsigned int id;
    std::string name;
    Texture* texture;
public:
    Sprite(Texture* inTexture, unsigned int inID, std::string inName);
    ~Sprite();
    unsigned int getID();
    std::string getName();
    SDL_Rect getTexture();
};

class Gui{
private:
    unsigned int id;
    std::string name;
    Texture* texture;
public:
    Gui(Texture* inTexture, unsigned int inID, std::string inName);
    ~Gui();
    unsigned int getID();
    std::string getName();
    SDL_Rect getTexture();
};


#endif /* Texture_hpp */
