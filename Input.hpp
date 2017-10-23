//
//  Input.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/12/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <map>
#include <queue>

//declared in Game
void quitGame();
//

enum command{
    aButton = 0,
    bButton = 1,
    xButton = 2,
    yButton = 3,
    startButton = 4,
    selectButton = 5
};

enum direction{
    up = 0,
    down = 1,
    left = 2,
    right = 3,
};

 //
class Input{
private:
    std::map<int, int> keys;
    std::queue<command> actionQueue;
    bool moveKeyHeld;
    direction d;
    
    //std::map<int, int> buttons;
    //bool gamepad; //if true then use buttons, else use keys;
public:
    Input();
    ~Input();
    void getInput();
    void onKeyDown(SDL_Event* event);
    void onKeyUp(SDL_Event* event);
    bool getKeyPress(SDL_Keycode key);
    int getCommand();
    bool isMoveKeyHeld();
    direction getMoveDirection();
};

#endif /* Input_hpp */
