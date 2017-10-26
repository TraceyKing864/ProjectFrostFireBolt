//
//  Character.hpp
//  Frost Insignia
//
//  Created by Tracey King on 4/10/17.
//  Copyright © 2017 Tracey King. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>

#include "TextureManager.hpp"
#include "Graphics.hpp"

struct charStats{
    int strength;
    int inteligence;
    int dexterity;
    int wisdom;
    int vitality;
    int constitution;
    int mind;
    int agility;
};

//Base stats
const int STR = 0;
const int INT = 1;
const int DEX = 2;
const int WIS = 3;
const int VIT = 4;
const int CON = 5;
const int MND = 6;
const int AGL = 7;

//Derived Stats:
const int MAXHP = 0;
const int CURHP = 1;
const int MAXMP = 2;
const int CURMP = 3;
const int ATK = 4;
const int DEF = 5;
const int CRT = 6;
const int MAG = 7;
const int RES = 8;
const int WIT = 9;
//Auxilary Combat Stats:
const int MOV = 10;
const int HIT = 11;
const int BLK = 12;
const int DGE = 13;
const int RSL = 14;
const int SPD = 15;
const int FTH = 16;

class CharacterClass;

class Character{
private:
    std::string name;
    std::string className;
    CharacterClass* characterClass;
    Sprite* sprite;
    int charLevel;
    int classLevel;

    //Character Base Stats (should never modify these aside from levelup):
    charStats base;
    
    //Character Applied Stats (these will be the stats that are obtained from class mod):
    charStats stats;
    
    //unsigned int spriteState;     //used for what the sprite should be doing
    //unsigned int direction;       //0 up, 1 down, 2 left, 3 right
    //combat stats:
protected:
    //Derived Stats:
    int maxhp;
    int curhp;
    int maxmp;
    int curmp;
    int atk;
    int def;
    int crt;
    int mag;
    int res;
    int wit;
    
    //Auxilary Combat Stats:
    int mov;
    int hit;
    int blk;
    int dge;
    int rsl;
    int spd;
    int fth;
    
public:
    Character(std::string inName, int inCharLevel, std::string inCharClass, int inClassLevel);
    Character(std::ifstream* file);
    ~Character();
    
    std::string getName();
    unsigned int getLevel();
    std::string getClassName();
    unsigned int getClassLevel();
    unsigned int getCurHP();
    unsigned int getMaxHP();
    unsigned int getCurMP();
    unsigned int getMaxMP();
    unsigned int getSpd();
    int getMov();
    int getAtkRng();
    
    void updateStats();
    void attack(Character* target);
    
    void render(Graphics* graphics, SDL_Rect* screenLoc);
    
    friend class Character;
    friend class CharacterClass;
    void levelUp();
    void changeClass(std::string charClass);
};

class CharacterClass{
private:
    int classID;
    std::string className;
    Sprite* sprite;
    
    //Percentage modifiers for character classes
    float modStrength;
    float modInteligence;
    float modDexterity;
    float modWisdom;
    float modVitality;
    float modConstitution;
    float modMind;
    float modAgility;
    
    //Levelup amount for stats
    charStats levelAmount;
    
    //Movement for this class
    int move;
    int atkRange;
    
    //Abilities for this class
    //AbilitySet abilities;
    //  Ability* ability1;
    //  Ability* ability2;
    //  Ability* ability3;
    //  Ability* ability4;
    
    //Weapons available for this class
    //bool canUseWeapon[9];
    
    //Equipment available for this class
    //bool canUseEquipment[3];
    
    
public:
    CharacterClass(std::string inClassName);
    CharacterClass();
    ~CharacterClass();
    
    void initCharacter(Character* inCharacter);
    void applyClassMod(charStats* inBaseStats, charStats* inStats);
    charStats getLevelUpStats();
    void setClass(std::string inClassName);
    int getMove();
    int getAtkRange();
    
    friend class Character;
};

#endif /* Character_hpp */
