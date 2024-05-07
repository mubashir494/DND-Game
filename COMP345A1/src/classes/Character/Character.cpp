#include "Character.h"
#include <iostream>
#include <random>
#include <algorithm>


Character::Character(const string& name, int level) : name(name), level(level) {
    generateAbilityScores(); // General ability score generation
    hitPoints = 0;
    armorClass = 0;
    damageBonus = 0;
    wornEquipment["Armor"] = nullptr;
    wornEquipment["Belt"] = nullptr;
    wornEquipment["Boots"] = nullptr;
    wornEquipment["Ring"] = nullptr;
    wornEquipment["Helmet"] = nullptr;
    wornEquipment["Shield"] = nullptr;
    wornEquipment["Weapon"] = nullptr;
    equipment = new ItemContainer();
    UpdateAttackBonus();
}




void Character::generateAbilityScores() {

    abilityScores["Strength"] = generateScore();
    abilityScores["Dexterity"] = generateScore();
    abilityScores["Constitution"] = generateScore();
    abilityScores["Intelligence"] = generateScore();
    abilityScores["Wisdom"] = generateScore();
    abilityScores["Charisma"] = generateScore();

    // Calculate modifiers
    for (const auto& score : abilityScores) {
        modifiers[score.first] = calculateModifier(score.second);
    }
}



void Character::UpdateAttackBonus() {
    attackBonus.clear();
    if (level >= 16)
    {
        attackBonus.push_back(level);
        attackBonus.push_back(level - 5);
        attackBonus.push_back(level - 10);
        attackBonus.push_back(level - 15);
    }
    else if (level >= 11)
    {

        attackBonus.push_back(level);
        attackBonus.push_back(level - 5);
        attackBonus.push_back(level - 10);
    }
    else if (level >= 6)
    {

        attackBonus.push_back(level);
        attackBonus.push_back(level - 5);
    }
    else
    {
        attackBonus.push_back(level);
    }
}

int Character::generateScore() {

    int rolls[4];
    int smallestIndex = 0;
    int smallestVal = 24;
    int sum = 0;

    for(int i = 0; i < 4; i++)
    {
        rolls[i] = rollDice(1, 6);
        if(rolls[i] < smallestVal)
        {
            smallestIndex = i;
            smallestVal = rolls[i];
        }
    }

    rolls[smallestIndex] = 0;

    for(int roll : rolls)
    {
        sum += roll;
    }

    return sum;
}

int Character::calculateModifier(int abilityScore) {
    return (abilityScore - 10) / 2;
}


int Character::rollDice(int numberOfDice, int diceSides) {
    random_device rd; // Obtain a random number from hardware
    mt19937 generator(rd()); // Seed the generator
    uniform_int_distribution<> distribution(1, diceSides);

    int total = 0;
    for (int i = 0; i < numberOfDice; ++i) {
        total += distribution(generator);
    }
    return total;
}



void Character::displayCharacterSheet() const {
    cout << "---------------------------------------------\n";
    cout << "Name: " << name << "\nLevel: " << level << "\n";

    for (const auto& score : abilityScores) {
        cout << score.first << ": " << score.second << " (Modifier: " << modifiers.at(score.first) << ")\n";
    }
    cout << "Hit Points: " << hitPoints << "\nArmor: " << armorClass
              << "\nAttack Bonus Per Round: ";
    for (const int& attackBonu : attackBonus){
        cout << attackBonu << " ";
    }
    cout << "\nDamage Bonus: " << damageBonus << "\n";

    // print the worn Item

    cout << "------------- Equipped Items: --------------" << endl;

    for (const auto& equipments : wornEquipment) {
        if(equipments.second != nullptr){
            equipments.second->printWeapon();
            cout << "\t\t---------------------------" << endl;
        }
    }


    // print the available equipment
    cout << "------------- Items Inventory: --------------" << endl;


    equipment->printContainer();


}

int Character::getArmorACValue(const std::string& armorName) {
    // Example armor AC values. In a real game, you'd look these up in a database or data structure.
    map<string, int> armorACValues = {
            {"Leather", 2},
            {"Chain Mail", 5},
            {"Plate", 8}
    };

    // Find the armor in the map and return its AC value, default to 0 if not found
    auto it = armorACValues.find(armorName);
    if (it != armorACValues.end()) {
        return it->second;
    } else {
        return 0; // No AC bonus for unrecognized armor
    }
}

void Character::adjustLevel(int level) {
    this->level = level;
    UpdateAttackBonus();
    calculateAttributes();
}

bool Character::equip(Item *item) {
    // Check is equipment is already equipped
    if(item->getEquipped()){
        cout << "This weapon is already equipped\n";
        return false;
    }
    // If item Exist in the container
    if(equipment->itemExist(item)){
       cout << "Item Already Exist in the Container \n";
       return false;

    }
    // Adds Item to the Container
    item->setEquipped(true);
    equipment->addItem(item);
    return true;
}

bool Character::unequip(int index) {
    Item *item  = equipment->getItem(index);
    if(item == nullptr){
        cout << "Equipment Not found";
        return false;
    }
    if(wornEquipment[item->getType()] == item){
        cout << "In order to remove the item from the equipment container please first remove it \n";
        return false;
    }

    return equipment->removeItem(index);
}

bool Character::wearItem(int index) {
    Item *item  = equipment->getItem(index);

    // If the Item does not exist in the equipment container
    if(item == nullptr){
        cout << "Error Occured\n";
        return false;
    }

    // Logic to change the Ability scores according to the worn item
    if(wornEquipment[item->getType()] != nullptr ){
        cout << "You are already wearing this type of equipment\n";
        return false;
    }


    // If everything is good then change the ability scores
    modifiers["Strength"] += item->getAbilityScores()["Strength"];
    modifiers["Dexterity"] += item->getAbilityScores()["Dexterity"] ;
    modifiers["Constitution"] += item->getAbilityScores()["Constitution"];
    modifiers["Intelligence"] += item->getAbilityScores()["Intelligence"];
    modifiers["Wisdom"] += item->getAbilityScores()["Wisdom"];
    modifiers["Charisma"] += item->getAbilityScores()["Charisma"];
    armorClass += item->getArmorClass();
    for (int & attackBonu : attackBonus) {
        attackBonu += item->getAttackBonus();
    }
    damageBonus += item->getDamageBonus();
    wornEquipment[item->getType()] = item;
    cout << "Successfully equipped item.\n";
    return true;
}

bool Character::remove(string type) {
    Item* wornItem = wornEquipment[type];
    if(wornItem == nullptr){
        cout << "No item equipped to remove\n";
        return false;
    }
    // If all is good then reverse the ability scores
    modifiers["Strength"] -= wornItem->getAbilityScores()["Strength"];
    modifiers["Dexterity"] -= wornItem->getAbilityScores()["Dexterity"] ;
    modifiers["Constitution"] -= wornItem->getAbilityScores()["Constitution"];
    modifiers["Intelligence"] -= wornItem->getAbilityScores()["Intelligence"];
    modifiers["Wisdom"] -= wornItem->getAbilityScores()["Wisdom"];
    modifiers["Charisma"] -= wornItem->getAbilityScores()["Charisma"];
    armorClass += wornItem->getArmorClass();
    for (int & attackBonu : attackBonus) {
        attackBonu -= wornItem->getAttackBonus();
    }
    damageBonus -= wornItem->getDamageBonus();
    wornEquipment[type] = nullptr;
    cout << "Successfully removed item and placed it in inventory.\n";
    return true;
}

void Character::onAttacked() {
    if(dynamic_cast<FriendlyStrategy*>(strategy)) { // If current strategy is FriendlyStrategy
        setStrategy(new AggressorStrategy()); // Switch to AggressorStrategy
        notify(name + " now seeks revenge for being attacked and is switching to the dark side  (Aggressor Strategy)");
        cout << name << " now seeks revenge for being attacked and is switching to the dark side  (Aggressor Strategy)";
    }
}

// Define the attack method in the Character class
bool Character::attack(Character* target, int attackRoll){
   // depending on the level the user is attack
   Dice dice;
   for(int attackBonu : attackBonus) {

       int totalAttack = attackRoll + attackBonu + modifiers["Strength"]; // Assume first attack bonus is used. You might want to choose based on context.

       cout << target->name << " currently has " << target->hitPoints << " hit points.\n";

       notify(name + " rolls the dice to attack: " + std::to_string(attackRoll) + " + " + std::to_string(attackBonus[0]) + " (bonus) => total = " + std::to_string(totalAttack) + "\n");

       if (totalAttack >= target->armorClass) {
           // roll to get the amount of damage
           int r = dice.roll("1d8") + modifiers["Strength"];

           // The attack hits
           notify("The attack Hits!");
           cout << name << " hits " << target->name << " for a total of " << r << " damage!\n";

           target->hitPoints -= r; // Apply damage
           cout << target->name << " now has " << std::max(0, target->hitPoints) << " hit points.\n";

           target->onAttacked(); // Notify the target that it's being attacked

           if(target->hitPoints <= 0 ){
               return true;
           }
           // Additional logic could be added here, such as checking if the target is defeated
       } else {
           // The attack misses
           cout << name << " misses " << target->name << ".\n";
       }
   }
   return false; // Attack missed

}

// Method to set the strategy
void Character::setStrategy(CharacterStrategy* newStrategy) {
    strategy = newStrategy;
}

// Delegating move and attack actions to the strategy
void Character::move(Map* map) {
    if (strategy) strategy->move(this, map);
    else std::cout << name << " has no strategy for moving." << std::endl;
}



void Character::attack(Map* map) {
    if (strategy) strategy->attack(this, map);
    else std::cout << name << " has no strategy for attacking." << std::endl;
}

// Optional: a method for actions not defined in all strategies
void Character::freeAction(Map* map){
    // Check if the strategy is of type HumanPlayerStrategy and cast it
    HumanPlayerStrategy* humanStrategy = dynamic_cast<HumanPlayerStrategy*>(strategy);
    if (humanStrategy) {
        humanStrategy->freeAction(this,map);
    } else {
        std::cout << name << " has no free actions to perform." << std::endl;
    }
}

void Character::attach(IObserver* observer) {
    observers.push_back(observer);
}

void Character::detach(IObserver* observer) {
    observers.remove(observer);
}

void Character::notify(const std::string& message) {
    if (loggingEnabled){
        for(auto observer : observers) {
            observer->update(message);
        }
    }
}


std::istream& operator>>(std::istream& is, Character& character) {
    // Reading character
    string strategy;
    is >> character.name >> character.level ;
    is >> strategy;
    // Get Strategy
    if(strategy == "Human"){
        HumanPlayerStrategy* humanPlayerStrategy = new HumanPlayerStrategy();
        character.setStrategy(humanPlayerStrategy);
    }
    else if (strategy == "Aggressor"){
        AggressorStrategy* aggressorStrategy = new AggressorStrategy();
        character.setStrategy(aggressorStrategy);
    }
    else if(strategy == "Friendly"){
        FriendlyStrategy* friendlyStrategy = new FriendlyStrategy();
        character.setStrategy(friendlyStrategy);
    }
    // Update Attack Bonus
    character.UpdateAttackBonus();

    is >> character.armorClass >> character.damageBonus >> character.hitPoints;
    is >> character.abilityScores.at("Strength");
    is >> character.abilityScores.at("Dexterity");
    is >> character.abilityScores.at("Constitution");
    is >> character.abilityScores.at("Intelligence");
    is >> character.abilityScores.at("Wisdom");
    is >> character.abilityScores.at("Charisma");
    is >> *character.equipment;

    int input;
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    is >> input;
    if(input != -1){
        character.wearItem(input);
    }
    return is;

}
std::ostream &operator<<(ostream &os, const Character &character) {
    // Writing Character
    os << character.name << " " << character.level << " ";
    os << character.strategy->getStrategyType() << " ";
    os << character.armorClass << " " << character.damageBonus << " " << character.hitPoints << " ";
    os << character.abilityScores.at("Strength") << " ";
    os << character.abilityScores.at("Dexterity") << " ";
    os << character.abilityScores.at("Constitution") << " ";
    os << character.abilityScores.at("Intelligence") << " ";
    os << character.abilityScores.at("Wisdom") << " ";
    os << character.abilityScores.at("Charisma") << " ";
    os << *character.equipment ;
    os << character.equipment->getItemIndex(character.wornEquipment.at("Armor")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Belt")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Boots")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Helmet")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Ring")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Shield")) << " ";
    os << character.equipment->getItemIndex(character.wornEquipment.at("Weapon")) << " ";
    return os;
}




