//
//  Input.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/12/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Input.hpp"


Input::Input(): actionQueue(){
    moveKeyHeld = false;
    d = up;
}
Input::~Input(){
    
}
void Input::onKeyDown(SDL_Event* event){
    keys[event->key.keysym.sym] = 1;
    switch(event->key.keysym.sym){
        case SDLK_w:
            moveKeyHeld = true;
            d = up;
            break;
        case SDLK_s:
            moveKeyHeld = true;
            d = down;
            break;
        case SDLK_a:
            moveKeyHeld = true;
            d = left;
            break;
        case SDLK_d:
            moveKeyHeld = true;
            d = right;
            break;
        case SDLK_j:
            actionQueue.push(command(aButton));
            break;
        case SDLK_k:
            actionQueue.push(command(bButton));
            break;
        case SDLK_l:
            actionQueue.push(command(xButton));
            break;
        case SDLK_i:
            actionQueue.push(command(yButton));
            break;
        case SDLK_u:
            actionQueue.push(command(startButton));
            break;
        case SDLK_o:
            actionQueue.push(command(selectButton));
            break;
    }
}
void Input::onKeyUp(SDL_Event* event){
    keys[event->key.keysym.sym] = 0;
    if(!keys[SDLK_w] && !keys[SDLK_a] && !keys[SDLK_s] && !keys[SDLK_d])
        moveKeyHeld = false;
}
void Input::getInput(){
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitGame();
                break;
            case SDL_KEYDOWN:
                onKeyDown(&event);
                break;
            case SDL_KEYUP:
                onKeyUp(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                break;
        }
    }
    if(keys[SDLK_ESCAPE])
        quitGame();
}
bool Input::getKeyPress(SDL_Keycode key){
    return keys[key];
}
int Input::getCommand(){
    if(actionQueue.empty())
        return -1;
    int i = actionQueue.front();
    while(!actionQueue.empty())
        actionQueue.pop();
    return i;
}
bool Input::isMoveKeyHeld(){
    return moveKeyHeld;
}
direction Input::getMoveDirection(){
    return d;
}