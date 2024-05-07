//
// Created by Oliver Hassan on 2024-03-23.
//

#ifndef COMP345A1_CHARACTERSTRATEGY_H
#define COMP345A1_CHARACTERSTRATEGY_H


#include "../Character/Character.h"
#include "../Map/Map.h"

class Character;

class CharacterStrategy {

public:
    virtual void move(Character* c, Map* map) = 0;
    virtual void attack(Character* source, Map* map) = 0;
    virtual ~CharacterStrategy() {}
    virtual string getStrategyType () = 0;

};



class HumanPlayerStrategy : public CharacterStrategy {

public:
    void move(Character* c, Map* map) override;
    void attack(Character* source, Map* map) override;
    void freeAction(Character* character,Map* map);
    void pickupItemFromChest(Character* character,Map* map);
    string getStrategyType() override {return  "Human";};
};



class AggressorStrategy : public CharacterStrategy {

public:
    void move(Character* c, Map* map) override;
    void attack(Character* source, Map* map) override;
    string getStrategyType() override {return  "Aggressor";};
};

class FriendlyStrategy : public CharacterStrategy {

public:
    void move(Character* c, Map* map) override;
    void attack(Character* source, Map* map) override;
    string getStrategyType() override {return  "Friendly";};
};


#endif //COMP345A1_CHARACTERSTRATEGY_H
