//
//  Game.cpp
//  Frost Insignia
//
//  Created by Tracey King on 4/6/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Game.hpp"

Game* Game::static_instance = NULL;

Game::Game(): frameSkip(0), graphics(), input(),
        running(0){
        TextureManager::instance();
}
Game::~Game(){
    stop();
}
Game* Game::instance(){
    if(!static_instance)
        static_instance = new Game();
    return static_instance;
}
void Game::getInput(){
    input.getInput();
}
void Game::draw(){
    graphics.clear();
    if(scene)
        scene->draw(&graphics);
    graphics.scale();
    graphics.present();
}
void Game::update(){
    if(scene)
        scene->update(&input);
    else
        quit();
}
void Game::start(){
    run();
}
void Game::stop() {
    delete scene;
    SDL_Quit();
    TTF_Quit();
}
void Game::fpsChanged(int fps) {
    std::cout << fps << std::endl;
}

void Game::quit() {
    running = 0;
}
//  run process is essentially;
//      input()
//      update()
//      render()
//  adds this to keep game running smoothly
//      sleep()
void Game::run(){
    running = true;
    int past = SDL_GetTicks();
    int now = past;
    int pastFps = past;
    int fps = 0;
    int framesSkipped = 0;
    //start first scene
    scene = new Scene();
    while (running){
        int timeElapsed = 0;
        getInput();
        now = SDL_GetTicks();
        timeElapsed = now - past;
        if (timeElapsed >= updateInterval){
            past = now;
            update();
            framesSkipped++;
            if (framesSkipped >= frameSkip){
                draw();
                fps++;
                framesSkipped = 0;
            }
        }
        if ((now - pastFps) >= 1000){
            pastFps = now;
            fpsChanged(fps);
            fps = 0;
        }
        SDL_Delay(1);
    }
}
void quitGame(){
    Game::instance()->quit();
}
int main(int argc, char** argv){
    Game::instance();
    Game::instance()->start();
    return 0;
}