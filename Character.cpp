//
//  Character.cpp
//  Frost Insignia
//
//  Created by Tracey King on 4/10/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#include "Character.hpp"

Character::Character(std::string inName, int inCharLevel, std::string inCharClass, int inClassLevel){
    name = inName;
    charLevel = 0;
    classLevel = inClassLevel;
    base.strength = 10;
    base.inteligence = 10;
    base.dexterity = 10;
    base.wisdom = 10;
    base.vitality = 10;
    base.constitution = 10;
    base.mind = 10;
    base.agility = 10;
    
    characterClass = new CharacterClass(inCharClass);
    characterClass->initCharacter(this);
    
    for(int i = 0; i < inCharLevel && i < 99; i++)
        levelUp();
    if(charLevel == 0)
        levelUp();
}
Character::Character(std::ifstream* file){
    /*
        eventually will read in persistent data for characters
    */
}
Character::~Character(){
    //delete characterClass;    for whatever reason can't delete, potential memory leak??? fix this at some point...
}
std::string Character::getName(){
    return name;
}
unsigned int Character::getLevel(){
    return charLevel;
}
std::string Character::getClassName(){
    return className;
}
unsigned int Character::getClassLevel(){
    return classLevel;
}
unsigned int Character::getCurHP(){
    return curhp;
}
unsigned int Character::getMaxHP(){
    return maxhp;
}
unsigned int Character::getCurMP(){
    return curmp;
}
unsigned int Character::getMaxMP(){
    return maxmp;
}
unsigned int Character::getSpd(){
    return spd;
}
int Character::getMov(){
    return characterClass->getMove();
}

void Character::updateStats(){
    maxhp = ((stats.vitality * 0.8) + (stats.strength * 0.2)) * 2.5;
    curhp = maxhp;
    maxmp = ((stats.mind * 0.8) + (stats.inteligence * 0.2)) * 2.5;
    curmp = maxmp;
    atk = ((stats.strength * 0.7) + (stats.dexterity * 0.3));
    def = ((stats.constitution * 0.8)) * 0.6;
    crt = ((stats.dexterity * 0.85) + (stats.wisdom * 0.15));
    mag = ((stats.inteligence * 0.7) + (stats.wisdom * 0.3));
    res = ((stats.mind * 0.8)) * 0.6;
    wit = ((stats.wisdom * 0.85) + (stats.dexterity * 0.15));
    
    hit = ((stats.agility * 0.85) + (stats.wisdom * 0.15));
    blk = ((stats.constitution * 0.85)) * 0.15;
    dge = ((stats.agility * 0.85)) * 0.15;
    rsl = ((stats.vitality * 0.3) + (stats.mind * 0.15) + (stats.constitution * 0.15));
    spd = ((stats.agility * 0.8) + (stats.dexterity * 0.2));
    fth = 0;
}
/*
void Character::setPlayer(int inPlayer){
    player = inPlayer;
}
int Character::getPlayer(){
    return player;
}
 */
void Character::levelUp(){
    charLevel++;
    charStats lvl = characterClass->getLevelUpStats();
    base.strength += lvl.strength;
    base.inteligence += lvl.inteligence;
    base.dexterity += lvl.dexterity;
    base.wisdom += lvl.wisdom;
    base.vitality += lvl.vitality;
    base.constitution += lvl.constitution;
    base.mind += lvl.mind;
    base.agility += lvl.agility;
    characterClass->applyClassMod(&base, &stats);
    updateStats();
}
void Character::render(Graphics* graphics, SDL_Rect* screenLoc){
    SDL_Rect imgLoc = sprite->getTexture();
    graphics->renderTexture(&imgLoc, screenLoc, 1);
}
void Character::changeClass(std::string charClass){
    
}
void Character::attack(Character* target){
    target->curhp -= (atk + 10) - target->def;
    if(target->curhp < 0)
        target->curhp = 0;
}




CharacterClass::CharacterClass(std::string inClassName){
    setClass(inClassName);
}
CharacterClass::CharacterClass(){
    classID = 0;
    className = "Warrior";
    sprite = TextureManager::instance()->getSprite(0);
    //Percentage modifiers for character classes
    modStrength = 0.5;
    modInteligence = 0.5;
    modDexterity = 0.5;
    modWisdom = 0.5;
    modVitality = 0.5;
    modConstitution = 0.5;
    modMind = 0.5;
    modAgility = 0.5;
    //Levelup amount for stats
    levelAmount.strength = 5;
    levelAmount.inteligence = 5;
    levelAmount.dexterity = 5;
    levelAmount.wisdom = 5;
    levelAmount.vitality = 5;
    levelAmount.constitution = 5;
    levelAmount.mind = 5;
    levelAmount.agility = 5;
    //Movement for this class
    move = 5;
}
CharacterClass::~CharacterClass(){
    
}

void CharacterClass::initCharacter(Character* inCharacter){
    inCharacter->sprite = sprite;
    inCharacter->mov = move;
    inCharacter->className = className;
    applyClassMod(&inCharacter->base, &inCharacter->stats);
}
void CharacterClass::applyClassMod(charStats* inBaseStats, charStats* inStats){
    inStats->strength = inBaseStats->strength * modStrength;
    inStats->inteligence = inBaseStats->inteligence * modInteligence;
    inStats->dexterity = inBaseStats->dexterity * modDexterity;
    inStats->wisdom = inBaseStats->wisdom * modWisdom;
    inStats->vitality = inBaseStats->vitality * modVitality;
    inStats->constitution = inBaseStats->constitution * modConstitution;
    inStats->mind = inBaseStats->mind * modMind;
    inStats->agility = inBaseStats->agility * modAgility;
}
charStats CharacterClass::getLevelUpStats(){
    return levelAmount;
}
void CharacterClass::setClass(std::string inClassName){
    if(inClassName == "Warrior")
        classID = 0;
    else if(inClassName == "Rogue")
        classID = 1;
    else if(inClassName == "Archer")
        classID = 2;
    else if(inClassName == "Mage")
        classID = 3;
    else
        classID = 0;
    
    switch(classID){
        case 0:
            className = "Warrior";
            sprite = TextureManager::instance()->getSprite(0);
            //Percentage modifiers for character classes
            modStrength = 0.5;
            modInteligence = 0.5;
            modDexterity = 0.5;
            modWisdom = 0.5;
            modVitality = 0.5;
            modConstitution = 0.5;
            modMind = 0.5;
            modAgility = 0.5;
            //Levelup amount for stats
            levelAmount.strength = 4;
            levelAmount.inteligence = 5;
            levelAmount.dexterity = 5;
            levelAmount.wisdom = 3;
            levelAmount.vitality = 6;
            levelAmount.constitution = 7;
            levelAmount.mind = 5;
            levelAmount.agility = 5;
            //Movement for this class
            move = 4;
            break;
        case 1:
            className = "Rogue";
            sprite = TextureManager::instance()->getSprite(1);
            //Percentage modifiers for character classes
            modStrength = 0.5;
            modInteligence = 0.5;
            modDexterity = 0.5;
            modWisdom = 0.5;
            modVitality = 0.5;
            modConstitution = 0.5;
            modMind = 0.5;
            modAgility = 0.5;
            //Levelup amount for stats
            levelAmount.strength = 6;
            levelAmount.inteligence = 5;
            levelAmount.dexterity = 7;
            levelAmount.wisdom = 5;
            levelAmount.vitality = 7;
            levelAmount.constitution = 4;
            levelAmount.mind = 5;
            levelAmount.agility = 6;
            //Movement for this class
            move = 6;
            break;
        case 2:
            className = "Archer";
            sprite = TextureManager::instance()->getSprite(2);
            //Percentage modifiers for character classes
            modStrength = 0.5;
            modInteligence = 0.5;
            modDexterity = 0.5;
            modWisdom = 0.5;
            modVitality = 0.5;
            modConstitution = 0.5;
            modMind = 0.5;
            modAgility = 0.5;
            //Levelup amount for stats
            levelAmount.strength = 5;
            levelAmount.inteligence = 5;
            levelAmount.dexterity = 5;
            levelAmount.wisdom = 3;
            levelAmount.vitality = 6;
            levelAmount.constitution = 4;
            levelAmount.mind = 5;
            levelAmount.agility = 5;
            //Movement for this class
            move = 5;
            break;
        case 3:
            className = "Mage";
            sprite = TextureManager::instance()->getSprite(3);
            //Percentage modifiers for character classes
            modStrength = 0.5;
            modInteligence = 0.5;
            modDexterity = 0.5;
            modWisdom = 0.5;
            modVitality = 0.5;
            modConstitution = 0.5;
            modMind = 0.5;
            modAgility = 0.5;
            //Levelup amount for stats
            levelAmount.strength = 7;
            levelAmount.inteligence = 7;
            levelAmount.dexterity = 4;
            levelAmount.wisdom = 6;
            levelAmount.vitality = 4;
            levelAmount.constitution = 4;
            levelAmount.mind = 7;
            levelAmount.agility = 5;
            //Movement for this class
            move = 5;
            break;
    }
}
int CharacterClass::getMove(){
    return move;
}

