//
//  Board.cpp
//  Frost Insignia
//
//  Created by Tracey King on 4/14/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Board.hpp"


Cell::Cell(){
    character = NULL;
    tile = NULL;
}
Cell::~Cell(){
    
}
void Cell::setTile(Tile* inTile){
    tile = inTile;
}
void Cell::setCharacter(Character* inCharacter){
    character = inCharacter;
}
Character* Cell::getCharacter(){
    return character;
}
Tile* Cell::getTile(){
    return tile;
}

Board::Board(std::string fileName){
    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cout << "Error Board::Board; file not found." << std::endl;
        std::exit(1);
    }
    //read in and initialize map file
    file >> width;
    file >> height;
    cell = new Cell*[width];
    for(int i = 0; i < width; i++)
        cell[i] = new Cell[width];
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            int t;
            file >> t;
            cell[i][j].setTile(TextureManager::instance()->getTile(t));
        }
    }
    //read in unit information
    std::string var[4];
    
    //Line 1 <numEnemyUnits> <numAllyUnits>
    int numEnemyUnits;
    file >> numEnemyUnits;
    int numAllyUnits;
    file >> numAllyUnits;
    
    //Line 2* <enemyCharacterDataForEachLine>
    for(int i = 0; i < numEnemyUnits; i++){
        file >> var[0];     //var1 = name
        file >> var[1];     //var2 = level
        file >> var[2];     //var2 = class
        file >> var[3];     //var4 = classLevel
        characterList[1].push_back(Character(var[0], std::stoi(var[1]), var[2], std::stoi(var[3])));
    }
    
    //Line 3* <loadFrom PlayerUnits.txt>
    std::ifstream playerUnits("saves/playerUnits.txt");
    if(!playerUnits.is_open()){
        std::cout << "Error Board::Board() playerunits.txt; file not found." << std::endl;
        std::exit(1);
    }
    for(int i = 0; i < numAllyUnits; i++){
        playerUnits >> var[0];     //var1 = name
        playerUnits >> var[1];     //var2 = level
        playerUnits >> var[2];     //var2 = class
        playerUnits >> var[3];     //var4 = classLevel
        characterList[0].push_back(Character(var[0], std::stoi(var[1]), var[2], std::stoi(var[3])));
    }
    playerUnits.close();
    
    //Line 4 <x> <y>...numEnemyUnits
    for(std::list<Character>::iterator it = characterList[1].begin(); it != characterList[1].end(); it++){
        file >> var[0];   //var1 = x
        file >> var[1];   //var2 = y
        setCharacter((unsigned int)std::stoi(var[0]), (unsigned int)std::stoi(var[1]), &(*it));
    }
    //Line 5 <x> <y>...numAllyUnits
    for(std::list<Character>::iterator it = characterList[0].begin(); it != characterList[0].end(); it++){
        file >> var[0];   //var1 = x
        file >> var[1];   //var2 = y
        setCharacter((unsigned int)std::stoi(var[0]), (unsigned int)std::stoi(var[1]), &(*it));
    }
    
    initTurnList();
    
    file.close();
}
Board::~Board(){
    for(int i = 0; i < width; i++)
        delete[] cell[i];
    delete[] cell;
}
unsigned int Board::getWidth(){
    return width;
}
unsigned int Board::getHeight(){
    return height;
}
Cell* Board::getCell(unsigned int inX, unsigned int inY){
    return &cell[inX][inY];
}
bool Board::findCell(Cell* inCell, int* inX, int* inY){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(&cell[i][j] == inCell){
                *inX = i;
                *inY = j;
                return true;
            }
        }
    }
    return false;
}
void Board::setCharacter(unsigned int inX, unsigned int inY, Character* inCharacter){
    cell[inX][inY].setCharacter(inCharacter);
}
Character* Board::getCharacter(unsigned int inX, unsigned int inY){
    return cell[inX][inY].getCharacter();
}
void Board::getCharacterLocation(Character* inCharacter, int* inX, int* inY){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(cell[i][j].getCharacter() == inCharacter){
                *inX = i;
                *inY = j;
            }
        }
    }
}
int Board::getPlayer(Character* inCharacter){
    for(int i = 0; i < players; i++){
        for(std::list<Character>::iterator it = characterList[i].begin(); it != characterList[i].end(); it++){
            if(inCharacter == &(*it))
                return i;
        }
    }
    return -1; //should not happen, but means player is not found
}
int Board::getPlayerAt(unsigned int inX, unsigned int inY){
    Character* temp = getCharacter(inX, inY);
    for(int i = 0; i < players; i++){
        for(std::list<Character>::iterator it = characterList[i].begin(); it != characterList[i].end(); it++){
            if(temp == &(*it))
                return i;
        }
    }
    return -1; //should not happen, but means player is not found
}
void Board::removeDeadCharacters(){
    for(int i = 0; i < players; i++){
        for(std::list<Character>::iterator it = characterList[i].begin(); it != characterList[i].end(); it++){
            if(it->getCurHP() == 0){
                int x = 0;
                int y = 0;
                getCharacterLocation(&(*it), &x, &y);
                cell[x][y].setCharacter(NULL);
                turnList.remove(&*it);
                characterList[i].erase(it);
            }
        }
    }
}
bool Board::checkIfLastPlayer(){
    if(characterList[0].empty()){
        return true;
    }else if(characterList[1].empty()){
        return true;
    }else{
        return false;
    }
}
void Board::initTurnList(){
    for(std::list<Character>::iterator it = characterList[0].begin(); it != characterList[0].end(); it++){
        turnList.push_back(&(*it));
    }
    for(std::list<Character>::iterator it = characterList[1].begin(); it != characterList[1].end(); it++){
        turnList.push_back(&(*it));
    }
    sortTurnList();
    currentTurn = turnList.front();
    
    //debug cout-ing
    std::cout << "Current turn: " << currentTurn->getName() << std::endl;
    //
}

//helper function for sorting characters by speed
//  note: can't be a function of Board:: due to how std::list.sort() is called
bool cmpCharSpd(Character* first, Character* second){
    return first->getSpd() > second->getSpd();
}
void Board::sortTurnList(){
    turnList.sort(cmpCharSpd);
    
    //debug cout-ing
    int i = 0;
    std::cout << "-----------------Initial Turn List-------------------" << std::endl;
    for(std::list<Character*>::iterator it = turnList.begin(); it != turnList.end(); it++){
        std::cout << "Turn " << i << ": " << (*it)->getName() << std::endl;
        i++;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
    //
}

Character* Board::getCurrentTurn(){
    return currentTurn;
}
Character* Board::nextTurn(){
    turnList.push_back(turnList.front());
    turnList.pop_front();
    currentTurn = turnList.front();
    
    //debug cout-ing
    int i = 0;
    std::cout << "-----------------Current Turn List-------------------" << std::endl;
    for(std::list<Character*>::iterator it = turnList.begin(); it != turnList.end(); it++){
        std::cout << "Turn " << i << ": " << (*it)->getName() << std::endl;
        i++;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "Current turn: " << currentTurn->getName() << std::endl;
    //
    
    return currentTurn;
}
void Board::render(Graphics* graphics){
    SDL_Rect imgLoc;        //  location for texture
    SDL_Rect screenLoc;     //  location on screen
    //render tiles
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            imgLoc = cell[i][j].getTile()->getTexture();
            screenLoc.w = imgLoc.w;
            screenLoc.h = imgLoc.h;
            screenLoc.x = screenLoc.w * i;
            screenLoc.y = screenLoc.h * j;
            graphics->renderTexture(&imgLoc, &screenLoc, 0);
            
            if(cell[i][j].getCharacter()){
                cell[i][j].getCharacter()->render(graphics, &screenLoc);
                int player = getPlayer(cell[i][j].getCharacter());
                if(player == 0)
                    imgLoc = TextureManager::instance()->getGui(15)->getTexture();
                else
                    imgLoc = TextureManager::instance()->getGui(16)->getTexture();
                graphics->renderTexture(&imgLoc, &screenLoc, GUIMAP);
            }
        }
    }
}

