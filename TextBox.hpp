//
//  Message.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/18/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef TextBox_hpp
#define TextBox_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "Graphics.hpp"
#include "TextureManager.hpp"
#include "Texture.hpp"

class Label{
public:
    std::string str;
    unsigned int x;
    unsigned int y;
    
    Label(std::string inStr, unsigned int inX, unsigned int inY);
    ~Label();
};

class TextBox{
private:
    unsigned int textBoxSizeX;
    unsigned int textBoxSizeY;
    unsigned int screenLocX;
    unsigned int screenLocY;
    
    std::vector<Label> textElements;
    Gui* gui[9];
    
    TTF_Font* font;
    SDL_Color textColor;
    
public:
    TextBox(unsigned int inTextBoxSizeX, unsigned int inTextBoxSizeY, unsigned int inScreenLocX, unsigned int inScreenLocY);
    ~TextBox();
    
    void newLabel(std::string inText, unsigned int inX, unsigned int inY);
    void editLabelString(unsigned int inID, std::string newString);
    void editLabelLoc(unsigned int inID, unsigned int inX, unsigned int inY);
    void render(Graphics* graphics);
    void throwSomeText(Graphics* graphics);
};
/*
class Menu{
private:
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    
    std::vector<Label> item;     //Note: x and y of these are in reference to the menu
    Label* highlighted;
    
public:
    Menu();
    ~Menu();
    void update(Input* input);
    void render(Graphics* graphics);
 
    void open();
    void close();
    void navigate(direction d);
    bool select();
    bool cancel();
    
};
*/

#endif /* TextBox_hpp */
