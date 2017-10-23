//
//  Scene.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/11/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Character.hpp"
#include "Board.hpp"
#include "Input.hpp"
#include "Cursor.hpp"
#include "Graphics.hpp"

/*
struct piece{   //unused currently, but keeping the idea in the code
    Character* character;
    int x;      //x location on board
    int y;      //y location on board
    int player; //player controlling the unit
};
*/

/*
class SceneManager{
private:
    
public:
    SceneManager();
    ~SceneManager();
    
    void loadScene(int sceneID);
    void unloadScene();
    void sceneTransition();
};
*/

class Scene{
private:
    int sceneState;
    Board* board;
    Cursor* cursor;
public:
    Scene();
    ~Scene();
    void loadScene(std::string fileName);
    void unloadScene();
    void update(Input* input);
    void draw(Graphics* graphics);
};




#endif /* Scene_hpp */
