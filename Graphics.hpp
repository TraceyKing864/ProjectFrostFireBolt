//
//  Graphics.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/15/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Graphics_hpp
#define Graphics_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>

class Graphics{
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    
    const unsigned int graphics_width = 640;
    const unsigned int graphics_height = 400;
    
    TTF_Font* font;
    
    /*
        const int tileLayer = 0;
        const int spriteLayer = 1;
        const int effectLayer = 2;
        const int interfaceLayer = 3;
        SDL_Texture textureLayer[4];
    */
    
    SDL_Texture* spriteMap;
    SDL_Texture* tileMap;
    SDL_Texture* guiMap;
public:
    Graphics();
    ~Graphics();
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    void clear();
    void renderTexture(SDL_Rect* imgLoc, SDL_Rect* screenLoc, int textureMap);
    void scale();
    void present();
    void loadTextureMaps();
};

#endif /* Graphics_hpp */
