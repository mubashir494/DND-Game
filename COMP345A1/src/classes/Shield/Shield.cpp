//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Shield.h"

Shield::Shield(const std::string& name) : Item(name) {

    CalculateAttributes();
}

string Shield::getType() const {
    return "Shield";
}

void Shield::CalculateAttributes() {

    armorClass = rollDice();
}
