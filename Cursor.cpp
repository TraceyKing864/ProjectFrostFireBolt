//
//  Cursor.cpp
//  Frost Insignia
//
//  Created by Tracey King on 5/13/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Cursor.hpp"

Cursor::Cursor(Board* inBoard): actionMenu(), activeCharacterTextBox(8, 4, 0, 312), targetCharacterTextBox(8, 4, 448, 312){
    board = inBoard;
    x = 0;
    y = 0;
    
    cursorState = 0;
    moving = false;
    distanceToMove = 0;
    gui = TextureManager::instance()->getGui(0);
    
    screenLocX = 0;
    screenLocY = 0;
    activeCharacterX = 0;
    activeCharacterY = 0;
    activeCharacter = NULL;
    targetCharacter = NULL;
    cellLocation = inBoard->getCell(x, y);
    
    activeCharacterTextBox.newLabel("Name: ", 24, 24);
    activeCharacterTextBox.newLabel("Class: ", 24, 36);
    activeCharacterTextBox.newLabel("Level: ", 96, 24);
    activeCharacterTextBox.newLabel("Class Level: ", 96, 36);
    activeCharacterTextBox.newLabel("HP: / ", 24, 48);
    activeCharacterTextBox.newLabel("MP: / ", 24, 60);
    
    targetCharacterTextBox.newLabel("Name: ", 24, 24);
    targetCharacterTextBox.newLabel("Class: ", 24, 36);
    targetCharacterTextBox.newLabel("Level: ", 96, 24);
    targetCharacterTextBox.newLabel("Class Level: ", 96, 36);
    targetCharacterTextBox.newLabel("HP: / ", 24, 48);
    targetCharacterTextBox.newLabel("MP: / ", 24, 60);
    
    nextCharacter(board->getCurrentTurn());
    
    updateTextBoxes();
}
Cursor::~Cursor(){
    
}
void Cursor::render(Graphics* graphics){
    SDL_Rect screenLoc;
    SDL_Rect imgLoc;
    
    if(cursorState == 1){
        imgLoc = TextureManager::instance()->getGui(5)->getTexture();
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        for(std::vector<Cell*>::iterator it = walkTiles.begin(); it != walkTiles.end(); it++){
            if(board->findCell(*it, &screenLoc.x, &screenLoc.y)){
                screenLoc.x = screenLoc.x * 24;
                screenLoc.y = screenLoc.y * 24;
                graphics->renderTexture(&imgLoc, &screenLoc, 2);
            }
        }
        
    }
    if(cursorState == 3){
        imgLoc = TextureManager::instance()->getGui(5)->getTexture();
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        for(std::vector<Cell*>::iterator it = attackTiles.begin(); it != attackTiles.end(); it++){
            if(board->findCell(*it, &screenLoc.x, &screenLoc.y)){
                screenLoc.x = screenLoc.x * 24;
                screenLoc.y = screenLoc.y * 24;
                graphics->renderTexture(&imgLoc, &screenLoc, 2);
            }
        }
        
    }
    
    imgLoc = gui->getTexture();
    screenLoc.x = screenLocX;
    screenLoc.y = screenLocY;
    screenLoc.w = imgLoc.w;
    screenLoc.h = imgLoc.h;
    
    graphics->renderTexture(&imgLoc, &screenLoc, 2);
    if(cursorState == 1)
        activeCharacter->render(graphics, &screenLoc);
    if(activeCharacter)
        activeCharacterTextBox.render(graphics);
    else if(cellLocation->getCharacter())
        activeCharacterTextBox.render(graphics);
    if(targetCharacter)
        targetCharacterTextBox.render(graphics);
    else if(activeCharacter && cellLocation->getCharacter())
        targetCharacterTextBox.render(graphics);
    actionMenu.render(graphics);
}
void Cursor::changeState(int change){
    cursorState = change;
    switch(cursorState){
        case 0:     //moving freely
            gui = TextureManager::instance()->getGui(0);
            break;
        case 1:     //moving activeCharacter
            gui = TextureManager::instance()->getGui(2);
            break;
        case 2:     //character is placed, selecting ability
            gui = TextureManager::instance()->getGui(5);
            break;
        case 3:     //selecting target
            gui = TextureManager::instance()->getGui(4);
        case 4:     //performing attack
            gui = TextureManager::instance()->getGui(4);
        default:
            break;
    }
}
bool Cursor::canMoveCursor(direction d){
    bool canMove = true;
    int height = board->getHeight();
    int width = board->getWidth();
    if(d == up){
        if(y > 0){
            canMove = true;
        }else{
            //add code; play error sound
            canMove = false;
        }
    }else if(d == down){
        if(y < height-1){
            canMove = true;
        }else{
            //add code; play error sound
            canMove = false;
        }
    }else if(d == left){
        if(x > 0){
            canMove = true;
        }else{
            //add code; play error sound
            canMove = false;
        }
    }else if(d == right){
        if(x < width-1){
            canMove = true;
        }else{
            //add code; play error sound
            canMove = false;
        }
    }else{
        canMove = false;
        std::cout << "Error in Cursor::canMoveCursor(); direction not specified." << std::endl;
    }
    return canMove;
}
bool Cursor::canMovePiece(direction d){
    bool canMove = false;
    if(d == up){
        if(canWalkOnTile(x, y-1)){
            if(board->getCell(x, y-1)->getCharacter() == NULL){
                canMove = true;
            }else if(board->getPlayerAt(x, y-1) != board->getPlayerAt(x, y)){
                canMove = true;
            }else{
                canMove = false;
            }
        }else{
            canMove = false;
        }
    }else if(d == down){
        if(canWalkOnTile(x, y+1)){
            if(board->getCell(x, y+1)->getCharacter() == NULL){
                canMove = true;
            }else if(board->getPlayerAt(x, y+1) != board->getPlayerAt(x, y)){
                canMove = true;
            }else{
                canMove = false;
            }
        }else{
            canMove = false;
        }
    }else if(d == left){
        if(canWalkOnTile(x-1, y)){
            if(board->getCell(x-1, y)->getCharacter() == NULL){
                canMove = true;
            }else if(board->getPlayerAt(x-1, y) != board->getPlayerAt(x, y)){
                canMove = true;
            }else{
                canMove = false;
            }
        }else{
            canMove = false;
        }
    }else if(d == right){
        if(canWalkOnTile(x+1, y)){
            if(board->getCell(x+1, y)->getCharacter() == NULL){
                canMove = true;
            }else if(board->getPlayerAt(x+1, y) != board->getPlayerAt(x, y)){
                canMove = true;
            }else{
                canMove = false;
            }
        }else{
            canMove = false;
        }
    }else{
        canMove = false;
        std::cout << "Error in Cursor::canMovePiece(); direction not specified." << std::endl;
    }
    if(!canMove){
        //add code; play error sound
    }
    return canMove;
}
bool Cursor::pickupPiece(){
    if(cellLocation->getCharacter() == characterTurn){
        activeCharacter = board->getCharacter(x, y);
        board->setCharacter(x, y, NULL);
        return true;
    }
    return false;
}
bool Cursor::placePiece(){
    if(cellLocation->getCharacter() == NULL){
        board->setCharacter(x, y, activeCharacter);
        return true;
    }
    return false;
}
int Cursor::updateScreenLoc(direction d){
    if(d == left){
        screenLocX -= move_speed;
    }else if (d == right){
        screenLocX += move_speed;
    }else if (d == up){
        screenLocY -= move_speed;
    }else if (d == down){
        screenLocY += move_speed;
    }
    else{
        std::cout << "Error in Character::updateScreenLoc(); direction not specified." << std::endl;
    }
    return move_speed;
}
void Cursor::updateTextBoxes(){
    Character* temp = NULL;
    if(activeCharacter)
        temp = activeCharacter;
    else if(cellLocation->getCharacter())
        temp = cellLocation->getCharacter();
    
    if(temp){
        activeCharacterTextBox.editLabelString(0, temp->getName());
        activeCharacterTextBox.editLabelString(1, temp->getClassName());
        activeCharacterTextBox.editLabelString(2, "LV:  " + std::to_string(temp->getLevel()));
        activeCharacterTextBox.editLabelString(3, "CLV: " + std::to_string(temp->getClassLevel()));
        activeCharacterTextBox.editLabelString(4, "HP: " + std::to_string(temp->getMaxHP()) + '/' + std::to_string(temp->getCurHP()));
        activeCharacterTextBox.editLabelString(5, "MP: " + std::to_string(temp->getMaxMP()) + '/' + std::to_string(temp->getCurMP()));
    }else{
        activeCharacterTextBox.editLabelString(0, "Name: ");
        activeCharacterTextBox.editLabelString(1, "Class: ");
        activeCharacterTextBox.editLabelString(2, "Level: ");
        activeCharacterTextBox.editLabelString(3, "Class Level: ");
        activeCharacterTextBox.editLabelString(4, "HP: / ");
        activeCharacterTextBox.editLabelString(5, "MP: / ");
    }
    
    temp = NULL;
    if(targetCharacter)
        temp = targetCharacter;
    else if(activeCharacter && cellLocation->getCharacter())
        temp = cellLocation->getCharacter();
    
    if(temp){
        targetCharacterTextBox.editLabelString(0, temp->getName());
        targetCharacterTextBox.editLabelString(1, temp->getClassName());
        targetCharacterTextBox.editLabelString(2, "LV:  " + std::to_string(temp->getLevel()));
        targetCharacterTextBox.editLabelString(3, "CLV: " + std::to_string(temp->getClassLevel()));
        targetCharacterTextBox.editLabelString(4, "HP: " + std::to_string(temp->getMaxHP()) + '/' + std::to_string(temp->getCurHP()));
        targetCharacterTextBox.editLabelString(5, "MP: " + std::to_string(temp->getMaxHP()) + '/' + std::to_string(temp->getCurHP()));
    }else{
        targetCharacterTextBox.editLabelString(0, "Name: ");
        targetCharacterTextBox.editLabelString(1, "Class: ");
        targetCharacterTextBox.editLabelString(2, "Level: ");
        targetCharacterTextBox.editLabelString(3, "Class Level: ");
        targetCharacterTextBox.editLabelString(4, "HP: / ");
        targetCharacterTextBox.editLabelString(5, "MP: / ");
    }
}
//  TODO: add movement functions
void Cursor::calculateWalkTiles(){
    int characterX = 0, characterY = 0;
    board->getCharacterLocation(characterTurn, &characterX, &characterY);
    int moveRange = characterTurn->getMov();
    
    //clear current list if not empty
    if(!walkTiles.empty())
        walkTiles.clear();
    
    //gets tiles that you can walk on
    calcRange(moveRange, characterX, characterY);
    
}
void Cursor::calcRange(int range, int charX, int charY){    //recursive
    //check and add new walkable tile
    Cell* toAdd = board->getCell(charX, charY);
    bool unique = true;
    for(std::vector<Cell*>::iterator it = walkTiles.begin(); it != walkTiles.end(); it++){
        if(*it == toAdd)
            unique = false;
    }
    if(unique)
        walkTiles.push_back(*&toAdd);
    
    //check neighbors
    if(range > 0){
        //up
        if(charY-1 >= 0)
            calcRange(range-1, charX, charY-1);
        //down
        if(charY+1 < board->getHeight())
            calcRange(range-1, charX, charY+1);
        //left
        if(charX-1 >= 0)
            calcRange(range-1, charX-1, charY);
        //right
        if(charX+1 < board->getWidth())
            calcRange(range-1, charX+1, charY);
    }
}
bool Cursor::canWalkOnTile(int inX, int inY){
    //if it fails any of these tests, return false
    if(!(inX >= 0 && inX < board->getWidth() && inY >= 0 && inY < board->getHeight())){
        return false;
    }
    Cell* check = board->getCell(inX, inY);
    for(std::vector<Cell*>::iterator it = walkTiles.begin(); it != walkTiles.end(); it++){
        if(*it == check)
            return true;
    }
    return false;
}
//  TODO: add attack range parameters
void Cursor::calcAtkRange(int range, int charX, int charY){
    //check and add new walkable tile
    Cell* toAdd = board->getCell(charX, charY);
    bool unique = true;
    for(std::vector<Cell*>::iterator it = attackTiles.begin(); it != attackTiles.end(); it++){
        if(*it == toAdd)
            unique = false;
    }
    if(unique)
        attackTiles.push_back(*&toAdd);
    
    //check neighbors
    if(range > 0){
        //up
        if(charY-1 >= 0)
            calcAtkRange(range-1, charX, charY-1);
        //down
        if(charY+1 < board->getHeight())
            calcAtkRange(range-1, charX, charY+1);
        //left
        if(charX-1 >= 0)
            calcAtkRange(range-1, charX-1, charY);
        //right
        if(charX+1 < board->getWidth())
            calcAtkRange(range-1, charX+1, charY);
    }
}
void Cursor::calculateAtkTiles(){
    int characterX = 0, characterY = 0;
    board->getCharacterLocation(characterTurn, &characterX, &characterY);
    int atkRange = characterTurn->getAtkRng();
    
    //clear current list if not empty
    if(!attackTiles.empty())
        attackTiles.clear();
    
    //gets tiles that you can walk on
    calcAtkRange(atkRange, characterX, characterY);
    
}
bool Cursor::canAtkTile(int inX, int inY){
    //if it fails any of these tests, return false
    if(!(inX >= 0 && inX < board->getWidth() && inY >= 0 && inY < board->getHeight())){
        return false;
    }
    Cell* check = board->getCell(inX, inY);
    for(std::vector<Cell*>::iterator it = attackTiles.begin(); it != attackTiles.end(); it++){
        if(*it == check)
            return true;
    }
    return false;
}
//

bool Cursor::isMoving(){
    return moving;
}
void Cursor::animateMove(){
    distanceToMove -= updateScreenLoc(movingDirection);
    if(distanceToMove <= 0)
        moving = false;
}
bool Cursor::moveCursor(direction d){
    if(canMoveCursor(d)){
        movingDirection = d;
        distanceToMove = 24;
        
        if(d == up)
            y--;
        else if(d == down)
            y++;
        else if(d == left)
            x--;
        else
            x++;
        cellLocation = board->getCell(x, y);
        
        updateTextBoxes();
        return moving = true;
    }
    return false;
}
bool Cursor::selectPiece(){
    if(pickupPiece()){
        activeCharacterX = x;
        activeCharacterY = y;
        changeState(1);
        return true;
    }
    return false;
}
bool Cursor::deselectPiece(){
    if(placePiece()){
        activeCharacter = NULL;
        changeState(0);
        return true;
    }
    return false;
}
bool Cursor::movePiece(direction d){
    if(canMovePiece(d)){
        movingDirection = d;
        distanceToMove = 24;
        
        if(d == up)
            y--;
        else if(d == down)
            y++;
        else if(d == left)
            x--;
        else
            x++;
        cellLocation = board->getCell(x, y);
        activeCharacterX = x;
        activeCharacterY = y;
        
        updateTextBoxes();
        return moving = true;
    }
    return false;
}
bool Cursor::openActionMenu(){
    if(!cellLocation->getCharacter()){
        placePiece();
        actionMenu.open();
        changeState(2);
        return true;
    }
    return false;
}
void Cursor::cancelActionSelect(){
    actionMenu.close();
    pickupPiece();
    changeState(1);
}
void Cursor::navigateActionMenu(direction d){
    actionMenu.navigate(d);
}
int Cursor::actionSelect(){
    int action = actionMenu.select();
    if(action == 2){        //defend selected
        actionMenu.close();
        changeState(4);
    }else if(action != 0){  //action selected, need target
        actionMenu.close();
        changeState(3);
        calculateAtkTiles();
        updateTextBoxes();
    }
    return action;      //if 0, invalid action
}
void Cursor::cancelTargetSelect(){
    autoMoveTo(activeCharacterX, activeCharacterY);
    actionMenu.open();
    changeState(2);
}
bool Cursor::selectTarget(){
    if(cellLocation->getCharacter()){
        if((board->getPlayer(activeCharacter) != board->getPlayerAt(x, y)) && canAtkTile(x, y)){
            targetCharacter = board->getCharacter(x, y);
            changeState(4);
            return true;
        }
        return false;
    }else
        return false;
}
bool Cursor::act(){
    return actionMenu.execute(activeCharacter, targetCharacter);
}
void Cursor::reset(){
    targetCharacter = NULL;
    activeCharacter = NULL;
    changeState(0);
    actionMenu.reset();
    updateTextBoxes();
}
void Cursor::nextCharacter(Character* nextCharacter){
    characterTurn = nextCharacter;
    int toX, toY;
    board->getCharacterLocation(characterTurn, &toX, &toY);
    autoMoveTo(toX, toY);
    calculateWalkTiles();
    selectPiece();
}
void Cursor::autoMove(){
    
}
void Cursor::autoMoveTo(unsigned int toX, unsigned int toY){
    x = toX;
    y = toY;
    screenLocX = toX * 24;
    screenLocY = toY * 24;
    cellLocation = board->getCell(x, y);
    updateTextBoxes();
    /* this was supposed to move slowly however until I figure this out, it'll jump
    if(toX > x){
        for(int i = x; i != toX; i++)
            moveCursor(right);
    }else{
        for(int i = x; i != toX; i--)
            moveCursor(left);
    }
    if(toY > y){
        for(int j = y; j != toY; j++)
            moveCursor(down);
    }else{
        for(int j = y; j != toY; j--)
            moveCursor(up);
    }
     */
}

                                   
ActionMenu::ActionMenu(){
    action[0] = 1;
    action[1] = 2;
    action[2] = 0;
    action[3] = 0;
    
    gui[0] = TextureManager::instance()->getGui(20);
    gui[1] = TextureManager::instance()->getGui(19);
    gui[2] = TextureManager::instance()->getGui(18);
    gui[3] = TextureManager::instance()->getGui(18);
    
    highlightedAction = 0;
    cursor = TextureManager::instance()->getGui(17);

    visible = false;

    screenLocX = 288;
    screenLocY = 312;
}
ActionMenu::~ActionMenu(){
    
}
void ActionMenu::render(Graphics* graphics){
    if(visible){
        SDL_Rect imgLoc;
        SDL_Rect screenLoc;
        //ability[0] - Attack
        imgLoc = gui[0]->getTexture();
        screenLoc.x = screenLocX + imgLoc.w;
        screenLoc.y = screenLocY;
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        graphics->renderTexture(&imgLoc, &screenLoc, 2);
        
        if(highlightedAction == 0){
            imgLoc = cursor->getTexture();
            graphics->renderTexture(&imgLoc, &screenLoc, 2);
        }
        //ability[1] - Defend
        imgLoc = gui[1]->getTexture();
        screenLoc.x = screenLocX + imgLoc.w;
        screenLoc.y = screenLocY + imgLoc.h;
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        graphics->renderTexture(&imgLoc, &screenLoc, 2);
        
        if(highlightedAction == 1){
            imgLoc = cursor->getTexture();
            graphics->renderTexture(&imgLoc, &screenLoc, 2);
        }
        //ability[2] - Primary Ability
        imgLoc = gui[2]->getTexture();
        screenLoc.x = screenLocX;
        screenLoc.y = screenLocY + (imgLoc.h / 2);
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        graphics->renderTexture(&imgLoc, &screenLoc, 2);
        
        if(highlightedAction == 2){
            imgLoc = cursor->getTexture();
            graphics->renderTexture(&imgLoc, &screenLoc, 2);
        }
        //ability[3] - Secondary Ability
        imgLoc = gui[3]->getTexture();
        screenLoc.x = screenLocX + (imgLoc.w * 2);
        screenLoc.y = screenLocY + (imgLoc.h / 2);
        screenLoc.w = imgLoc.w;
        screenLoc.h = imgLoc.h;
        graphics->renderTexture(&imgLoc, &screenLoc, 2);
        
        if(highlightedAction == 3){
            imgLoc = cursor->getTexture();
            graphics->renderTexture(&imgLoc, &screenLoc, 2);
        }
    }
}
void ActionMenu::open(){
    visible = true;
}
void ActionMenu::close(){
    visible = false;
}
void ActionMenu::navigate(direction d){
    highlightedAction = d;
}
int ActionMenu::select(){
    return action[highlightedAction];
}
bool ActionMenu::execute(Character* actor, Character* target){
    if(action[highlightedAction] == 1){         //perform attack
        actor->attack(target);
        return true;
    }else if(action[highlightedAction] == 2){   //perform primary ability
        //actor->primaryAbility();
        return true;
    }else if(action[highlightedAction] == 3){   //perform secondary ability
            //actor->secondaryAbility();
            return true;
    }else{                                      //perform defend
        return true;
    }
}
void ActionMenu::reset(){
    highlightedAction = 0;
    visible = false;
}








