//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Armor.h"


Armor::Armor(const std::string& name) : Item(name)  {
  
    CalculateAttributes();
}

std::string Armor::getType() const {
    return "Armor";
}

void Armor::CalculateAttributes() {
    armorClass = rollDice();
}
