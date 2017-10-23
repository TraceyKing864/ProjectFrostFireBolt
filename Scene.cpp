//
//  Scene.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/11/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(){
    loadScene("gameFiles/scene.txt");
}
Scene::~Scene(){
}
void Scene::loadScene(std::string fileName){
    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cout << "Error Scene::loadScene; file not found." << std::endl;
        std::exit(1);
    }
    std::string var[4];
    
    //Line x <mapFileName>
    file >> var[0];
    board = new Board(var[0]);  //var1 = fileName
    
    cursor = new Cursor(board);
    file.close();
}
void Scene::unloadScene(){
    delete cursor;
    delete board;
}
void Scene::update(Input* input){
    //action();
    //  move();
    //  attack();
    //  primaryClassAbility();
    //      ability1();
    //      ability2();
    //      ability3();
    //      ability4();
    //  secondaryClassAbility();
    //      ability1();
    //      ability2();
    //      ability3();
    //      ability4();
    
    /*the return to int action can be
        -1 is no action
        aButton = 0
        bButton = 1
        xButton = 2
        yButton = 3
        startButton = 4
        selectButton = 5
    */
    int command = input->getCommand();
    bool moveKeyPress = input->isMoveKeyHeld();
    direction d = input->getMoveDirection();
    
    switch(sceneState){
        case 0:     //select unit
            if(cursor->isMoving()){
                cursor->animateMove();
            }else if(command == 0){
                if(cursor->selectPiece()){
                    sceneState = 1;
                }
            }else if(moveKeyPress){
                cursor->moveCursor(d);
            }
            break;
        case 1:     //move unit
            if(cursor->isMoving()){
                cursor->animateMove();
            }else if(command == 1){
                if(cursor->deselectPiece())
                    sceneState = 0;
            }else if(command == 0){
                if(cursor->openActionMenu()){
                    sceneState = 2;
                }
            }else if(moveKeyPress){
                cursor->movePiece(d);
            }
            break;
        case 2:     //select action
            if(command == 0){
                int action = cursor->actionSelect();
                if(action == 2)
                    sceneState = 4;
                else if(action != 0)
                    sceneState = 3;
            }
            else if(command == 1){
                cursor->cancelActionSelect();
                sceneState = 1;
            }else if(moveKeyPress){
                cursor->navigateActionMenu(d);
            }
            break;
        case 3:     //select target
            if(cursor->isMoving()){
                cursor->animateMove();
            }else if(command == 0){
                if(cursor->selectTarget()){
                    sceneState = 4;
                }
            }else if(command == 1){
                cursor->cancelTargetSelect();
                    sceneState = 2;
            }else if(moveKeyPress){
                cursor->moveCursor(d);
            }
            break;
        case 4:     //perform action and select next character's turn
            if(cursor->act()){      //returns if done
                board->removeDeadCharacters();  //check to see if anyone died
                cursor->reset();
                sceneState = 0;
                if(board->checkIfLastPlayer()){ //current win condition for game
                    std::cout << "PLAYER HAS WON...ENDING NOW" << std::endl;
                    quitGame();
                }
            }
            break;
        default:
            std::cout << "YA DINGUS HOW DID YOU EVEN GET HERE???" << std::endl;
            break;
    }
    
}
void Scene::draw(Graphics* graphics){
    //draw board
    board->render(graphics);
    //temp draw cursor
    cursor->render(graphics);
}