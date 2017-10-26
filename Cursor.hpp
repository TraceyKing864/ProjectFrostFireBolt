//
//  Cursor.hpp
//  Frost Insignia
//
//  Created by Tracey King on 5/13/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Cursor_hpp
#define Cursor_hpp

#include "Character.hpp"
#include "Input.hpp"
#include "Board.hpp"
#include "Graphics.hpp"
#include "TextBox.hpp"

/*enum CursorType{
    single,
    group,
    largeGroup,
    all
};*/

class ActionMenu{
private:
    Gui* gui[4];
    Gui* cursor;
    int action[4];
    int highlightedAction;
    bool visible;
    
    //this is the location for the entire ability selection box
    unsigned int screenLocX;
    unsigned int screenLocY;
public:
    ActionMenu();
    ~ActionMenu();
    void render(Graphics* graphics);
    
    void open();
    void close();
    void navigate(direction d);
    int select();
    
    bool execute(Character* actor, Character* target);
    
    void reset();
};

class Cursor{
private:
    Gui* gui;
    
    const int move_speed = 4;    //how fast the cursor/characters move
    bool moving;
    direction movingDirection;
    int distanceToMove;
    unsigned int x;     //location on board
    unsigned int y;
    int cursorState;
    unsigned int activeCharacterX;
    unsigned int activeCharacterY;
    
    ActionMenu actionMenu;
    TextBox activeCharacterTextBox;
    TextBox targetCharacterTextBox;
    
    Character* activeCharacter;
    Character* targetCharacter;
    //Eventually will be Character** targets;
    Cell* cellLocation;
    Board* board;
    
    //  TODO: add current character data
    Character* characterTurn;
    std::vector<Cell*> walkTiles;
    std::vector<Cell*> attackTiles;
    //
    
    void changeState(int change);
    bool canMoveCursor(direction d);
    bool canMovePiece(direction d);
    bool pickupPiece();
    bool placePiece();
    int updateScreenLoc(direction d);
    void updateTextBoxes();
    
    //  TODO: add movement parameters
    void calcRange(int range, int charX, int charY);
    void calculateWalkTiles();
    bool canWalkOnTile(int inX, int inY);
    
    //  TODO: add attack range parameters
    void calcAtkRange(int range, int charX, int charY);
    void calculateAtkTiles();
    bool canAtkTile(int inX, int inY);
    //
    
public:
    unsigned int screenLocX;
    unsigned int screenLocY;
    
    Cursor(Board* inBoard);
    ~Cursor();
    void render(Graphics* graphics);
    
    bool isMoving();    //maybe change to isPerformingAction?
    void animateMove();
    
    //actions to be performed by update();
    //state 0 - move cursor
    bool moveCursor(direction d);
    bool selectPiece();     //goto state 1 if true
    
    //state 1 - moving piece
    bool deselectPiece();   //goto state 0 if can place unit there
    bool movePiece(direction d);
    bool openActionMenu();  //goto state 2 if can place unit there
    
    //state 2 - choose action
    void cancelActionSelect();  //goto state 1
    void navigateActionMenu(direction d);
    int actionSelect();    //goto state 3 if valid action is selected
    
    //state 3 - select target(s)
    //moveCursor/isMoving is used here to select target
    void cancelTargetSelect();
    bool selectTarget();    //returns if valid target is selected
    
    //state 4 - perform action
    bool act();     //returns if finished using action
    void reset();   //resets cursor to unused state
    
    //  @TODO: add movement confined to grid
    void nextCharacter(Character* nextCharacter);
    void autoMove();
    void autoMoveTo(unsigned int toX, unsigned int toY);
    
    //
    
};



#endif /* Cursor_hpp */
