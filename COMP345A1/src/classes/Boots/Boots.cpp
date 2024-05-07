//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Boots.h"


Boots::Boots(const std::string& name) : Item(name) {
    CalculateAttributes();
}

string Boots::getType() const {
    return "Boots";
}

void Boots::CalculateAttributes() {
    armorClass = rollDice();
    abilityScores["Dexterity"] = rollDice();
}
