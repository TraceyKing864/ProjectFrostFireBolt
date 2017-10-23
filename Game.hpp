//
//  Game.hpp
//  Frost Insignia
//
//  Created by Tracey King on 4/6/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Scene.hpp"
#include <SDL2_ttf/SDL_ttf.h>

class Game{
private:
    const int frameSkip = 0;
    const float updateInterval = 1000/60;
    bool running;
    Graphics graphics;
    //Sounds sounds
    Input input;  //used for game input
    //Clock clock ???
    //SceneManager sceneManager
    Scene* scene;           //used for specific level infromation
    
    static Game* static_instance;
    Game();
    ~Game();
    
    void stop();
    void fpsChanged(int fps);
    void run();
    void getInput();
    void draw();
    void update();
public:
    static Game* instance();
    void start();
    void quit();
};

extern void quitGame();


#endif /* Game_hpp */
