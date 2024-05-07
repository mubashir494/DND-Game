//
// Created by hp on 18/03/2024.
//

#include "BullyBuilder.h"
#include <algorithm>

void BullyBuilder::setAbilityScores() {
    int ability[6] = {
            fighter->getAbilityScores()["Strength"],
            fighter->getAbilityScores()["Dexterity"],
            fighter->getAbilityScores()["Constitution"],
            fighter->getAbilityScores()["Intelligence"],
            fighter->getAbilityScores()["Wisdom"],
            fighter->getAbilityScores()["Charisma"]

    };
    std::sort(ability,ability+6);
    std::reverse(ability,ability+6);

    fighter->setAbilityScores("Strength",ability[0]);
    fighter->setAbilityScores("Constitution",ability[1]);
    fighter->setAbilityScores("Dexterity",ability[2]);
    fighter->setAbilityScores("Intelligence",ability[3]);
    fighter->setAbilityScores("Charisma",ability[4]);
    fighter->setAbilityScores("Wisdom",ability[5]);


}
