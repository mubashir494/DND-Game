//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Weapon.h"



Weapon::Weapon(const std::string& name,const WeaponType& weaponType) : Item(name) {
    this->weaponType = weaponType;
    CalculateAttributes();
}

std::string Weapon::getType() const {
    return "Weapon";
}

void Weapon::CalculateAttributes() {
    attackBonus = rollDice();
    damageBonus = rollDice();
}

Weapon::WeaponType Weapon::getWeaponType() {
    return weaponType;
}


