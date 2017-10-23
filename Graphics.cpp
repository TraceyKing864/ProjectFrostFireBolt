//
//  Graphics.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/15/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Graphics.hpp"

Graphics::Graphics(){
    renderer = NULL;
    window = NULL;
    font = NULL;
    int flags = SDL_WINDOW_RESIZABLE;
    
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        return;
    }
    if(TTF_Init() == -1){
        return;
    }
    if(SDL_CreateWindowAndRenderer(graphics_width, graphics_height, flags, &window, &renderer)){
        return;
    }
    
    font = TTF_OpenFont("Arial Bold.ttf", 12);
    
    char windowTitle[128];
    sprintf(windowTitle, "Frost Insignia v0.01.05");
    SDL_SetWindowTitle(window, windowTitle);
    loadTextureMaps();
}
Graphics::~Graphics(){
    if(renderer != NULL){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if(window != NULL){
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_DestroyTexture(spriteMap);
    SDL_DestroyTexture(tileMap);
    SDL_DestroyTexture(guiMap);
}
SDL_Renderer* Graphics::getRenderer(){
    return renderer;
}
TTF_Font* Graphics::getFont(){
    return font;
}
void Graphics::clear(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}
void Graphics::renderTexture(SDL_Rect* imgLoc, SDL_Rect* screenLoc, int textureMap){
    if(textureMap == 0){
        SDL_RenderCopy(renderer, tileMap, imgLoc, screenLoc);
    }else if(textureMap == 1){
        SDL_RenderCopy(renderer, spriteMap, imgLoc, screenLoc);
    }else if(textureMap == 2){
        SDL_RenderCopy(renderer, guiMap, imgLoc, screenLoc);
    }
    else{
        std::cout << "something went wrong in Graphics::renderTexture fam." << std::endl;
    }
}
void Graphics::scale(){
    SDL_RenderSetLogicalSize(renderer, graphics_width, graphics_height);
}
void Graphics::present(){
    SDL_RenderPresent(renderer);
}
void Graphics::loadTextureMaps(){
    spriteMap = IMG_LoadTexture(renderer, "spriteTextureMap.png");
    tileMap = IMG_LoadTexture(renderer, "tileTextureMap.png");
    guiMap = IMG_LoadTexture(renderer, "guiTextureMap.png");
}

