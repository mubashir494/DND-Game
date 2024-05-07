//
// Created by Roger Sioufi on 2024-02-18.
//

#include "Item.h"


Item::Item(const string& name): name(name){
    equipped = false;
    initializeAttributes();
}

Item::~Item()= default;



std::string Item::getName() const {
    return name;
}

int Item::rollDice() {
    Dice dice;
    int em = dice.roll("1d6");
    while (em > 5)
    {
        em = dice.roll("1d6");
    }
    return em;
}

void Item::initializeAttributes() {
    abilityScores["Strength"] = 0;
    abilityScores["Dexterity"] = 0;
    abilityScores["Constitution"] = 0;
    abilityScores["Intelligence"] = 0;
    abilityScores["Wisdom"] = 0;
    abilityScores["Charisma"] = 0;
    armorClass = 0;
    hitPoints = 0;
    attackBonus = 0;
    damageBonus = 0;
}

void Item::printWeapon() {
    cout << "Item: "<< getType() << "\n";
    cout << "Item Name: "<< name << "\n";

    cout << "Armor: " << armorClass << "\n";
    cout << "Hit Points: "<< hitPoints << "\n";
    cout << "damage Bonus: "<<damageBonus << "\n";
    for (const auto& score : abilityScores) {
        cout << score.first << ": " << score.second << "s\n";
    }

}

std::ostream &operator<<(ostream &os, const Item &Item) {
    os <<  Item.name << " " << Item.equipped << " "<<Item.hitPoints<< " " <<Item.attackBonus<<" "<<Item.armorClass<< " "<<Item.damageBonus << " ";
    os << Item.abilityScores.at("Strength") << " " <<  Item.abilityScores.at("Dexterity") << " " <<  Item.abilityScores.at("Constitution") << " ";
    os << Item.abilityScores.at("Intelligence") << " "<< Item.abilityScores.at("Wisdom") << " " << Item.abilityScores.at("Charisma") << " ";
    return os;
}

std::istream& operator>>(std::istream& is, Item& item) {
    is >> item.name >> item.equipped >> item.hitPoints >> item.attackBonus >> item.armorClass >> item.damageBonus;
    is >> item.abilityScores["Strength"] >> item.abilityScores["Dexterity"] >> item.abilityScores["Constitution"];
    is >> item.abilityScores["Intelligence"] >> item.abilityScores["Wisdom"] >> item.abilityScores["Charisma"];
    return is;
}
