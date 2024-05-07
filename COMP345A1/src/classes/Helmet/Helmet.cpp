//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Helmet.h"


Helmet::Helmet(const std::string& name) : Item(name) {
    CalculateAttributes();
}

string Helmet::getType() const {
    return "Helmet";
}

void Helmet::CalculateAttributes() {
    abilityScores["Wisdom"] = rollDice();
    abilityScores["Intelligence"] = rollDice();
    armorClass = rollDice();
}
