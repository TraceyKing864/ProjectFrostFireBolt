//
//  TextBox.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/18/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "TextBox.hpp"

Label::Label(std::string inStr, unsigned int inX, unsigned int inY){
    str = inStr;
    x = inX;
    y = inY;
}
Label::~Label(){
    
}

TextBox::TextBox(unsigned int inTextBoxSizeX, unsigned int inTextBoxSizeY, unsigned int inScreenLocX, unsigned int inScreenLocY){
    textBoxSizeX = inTextBoxSizeX;
    textBoxSizeY = inTextBoxSizeY;
    screenLocX = inScreenLocX;
    screenLocY = inScreenLocY;
    int id = 6;
    for(int i = 0; i < 9; i++){
        gui[i] = TextureManager::instance()->getGui(id);
        id++;
    }
    textColor = {0, 0, 0};
    font = NULL;
}
TextBox::~TextBox(){
    
}

void TextBox::render(Graphics* graphics){
    SDL_Rect imgLoc;
    SDL_Rect screenLoc;
    for(int j = 0; j < textBoxSizeY; j++){
        for(int i = 0; i < textBoxSizeX; i++){
            if(j == 0){
                if(i == 0){
                    //top left
                    imgLoc = gui[0]->getTexture();
                }else if(i == (textBoxSizeX-1)){
                    //top right
                    imgLoc = gui[2]->getTexture();
                }else{
                    //top middle
                    imgLoc = gui[1]->getTexture();
                }
            }else if(j == (textBoxSizeY-1)){
                if(i == 0){
                    //bottom left
                    imgLoc = gui[6]->getTexture();
                }else if(i == (textBoxSizeX-1)){
                    //bottom right
                    imgLoc = gui[8]->getTexture();
                }else{
                    //bottom middle
                    imgLoc = gui[7]->getTexture();
                }
            }else{
                if(i == 0){
                    //left
                    imgLoc = gui[3]->getTexture();
                }else if(i == (textBoxSizeX-1)){
                    //right
                    imgLoc = gui[5]->getTexture();
                }else{
                    //middle
                    imgLoc = gui[4]->getTexture();
                }
            }
            //render textbox texture
            screenLoc.w = imgLoc.w;
            screenLoc.h = imgLoc.h;
            screenLoc.x = (imgLoc.w * i) + screenLocX;
            screenLoc.y = (imgLoc.h * j) + screenLocY;
            graphics->renderTexture(&imgLoc, &screenLoc, 2);
        }
    }

    if(font == NULL)
        font = graphics->getFont();
    SDL_Renderer* renderer= graphics->getRenderer();
    for(std::vector<Label>::iterator it = textElements.begin(); it != textElements.end(); it++){
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, it->str.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
        screenLoc.x = it->x + screenLocX;
        screenLoc.y = it->y + screenLocY;
        screenLoc.h = textSurface->h;
        screenLoc.w = textSurface->w;
        //render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &screenLoc);
    
        //BECAUSE I'M FREEEEEEEEEEEE-ing STRUCTURESSSS
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}
void TextBox::newLabel(std::string inText, unsigned int inX, unsigned int inY){
    textElements.push_back(Label(inText, inX, inY));
}
void TextBox::editLabelString(unsigned int inID, std::string newString){
    textElements[inID].str = newString;
}
void TextBox::editLabelLoc(unsigned int inID, unsigned int inX, unsigned int inY){
    textElements[inID].x = inX;
    textElements[inID].y = inY;
}