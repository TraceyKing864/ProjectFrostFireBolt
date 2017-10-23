//
//  GameMap.hpp
//  Frost Insignia
//
//  Created by Tracey King on 4/14/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include "TextureManager.hpp"
#include "Character.hpp"
#include "Graphics.hpp"
#include <queue>

class Cell{
private:
    Tile* tile;
    Character* character;
    //Obstacle* obstacle;
public:
    Cell();
    ~Cell();
    void setTile(Tile* inTile);
    void setCharacter(Character* inCharacter);
    Character* getCharacter();
    Tile* getTile();
};

class Board{
private:
    unsigned int width;
    unsigned int height;
    Cell** cell;
    //characters currently on the board
    const int players = 2;
    std::list<Character> characterList[2];
    //  TODO: implement this, add movement/turn order to cursor
    std::list<Character*> turnList;
    Character* currentTurn;
    bool cmpCharSpd(const Character& first, const Character& second);
    //
public:
    Board(std::string fileName);
    ~Board();
    unsigned int getWidth();
    unsigned int getHeight();
    Cell* getCell(unsigned int inX, unsigned int inY);
    void setCharacter(unsigned int inX, unsigned int inY, Character* inCharacter);
    Character* getCharacter(unsigned int inX, unsigned int inY);
    void getCharacterLocation(Character* inCharacter, int* x, int* y);  //returns values in the pass in x and y
    int getPlayer(Character* inCharacter);
    int getPlayerAt(unsigned int inX, unsigned int inY);
    void removeDeadCharacters();
    bool checkIfLastPlayer();
    // TODO: implement these
    void initTurnList();
    void sortTurnList();
    Character* getCurrentTurn();
    Character* nextTurn();
    //
    void render(Graphics* graphics);
};


#endif /* Board_hpp */
