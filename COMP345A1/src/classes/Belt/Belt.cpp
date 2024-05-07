#include "Belt.h"


Belt::Belt(const std::string& name) : Item(name) {
    CalculateAttributes();
}

std::string Belt::getType() const {
    return "Belt";
}

void Belt::CalculateAttributes() {
    abilityScores["Strength"] = rollDice();
    abilityScores["Constitution"] = rollDice();
}
