#pragma once

#include <string>
#include <map>
#include <vector>
#include "../ObserverPattern/Subject.h"
#include "../CellContent/CellContent.h"
#include "../ItemContainer/ItemContainer.h"
#include "../Weapon/Weapon.h"
#include "../CharacterStrategy/CharacterStrategy.h"
#include <list>
#include "../Weapon/Weapon.h"
#include "../GameLogger/GameLogger.h"

using namespace std;

class Map;
class CharacterStrategy;
class ItemContainer;
class Item;
class Weapon;

/**
 * @file Character.h
 * @brief Defines the base class for all characters in a Basic Fantasy RPG setting.
 *
 * This file contains the declaration of the Character class, which serves as the foundation for all character types
 * in the game. It includes basic attributes, equipment handling, and the framework for derived attribute calculations.
 *
 * Game Rules Involved:
 * - Ability scores (Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma) impact various character capabilities.
 * - Hit Points represent the character's health. They are determined by the character's level and Constitution modifier.
 * - Armor Class (AC) determines how difficult it is for enemies to hit the character in combat, affected by the equipped armor.
 * - Attack Bonus and Damage Bonus are derived from ability scores and affect combat effectiveness.
 *
 * Design Brief:
 * The Character class abstracts the common functionalities and attributes of all characters in the game. It uses virtual
 * functions for attribute calculations to allow derived classes to implement specific rules and behaviors. This design
 * promotes code reuse and flexibility, enabling easy extension for different character classes.
 *
 * Libraries Used:
 * - `<string>`: For representing character names and equipment in a human-readable format.
 * - `<map>`: To associate character attributes, modifiers, and equipment slots with their respective values and Items.
 *    Chosen for its efficient key-value storage and easy retrieval of character-related data.
 */

class Character: public Subject, public CellContent, public IObservable{
public:
    Character()  = default;

    int currentMap = 0;

    int hitPoints;

    void attach(IObserver* observer) override;

    void detach(IObserver* observer) override;

    void notify(const std::string& message) override;

    Character(const string& name, int level);

    CharacterStrategy* strategy = nullptr;

    // Method to set the strategy
    void setStrategy(CharacterStrategy* newStrategy);
    // Delegating move and attack actions to the strategy
    void move(Map* map);

    void attack(Map* map);

    void freeAction(Map* map);

    /**
    * @brief Virtual destructor for the Character class.
    *
    * Ensures derived classes are correctly cleaned up. This destructor is virtual to allow for proper cleanup of derived class objects through base class pointers.
    */
    virtual ~Character() = default;

    // getter methods
    map<string, int> getAbilityScores()  { return abilityScores; };
    map<string, int> getModifiers()  { return modifiers; };
    vector<int> getAttackBonus() const { return attackBonus; };


    int getWisdom() { return  abilityScores["Wisdom"];};
    int getConstitution() {return abilityScores["Constitution"];};
    int getIntelligence() {return abilityScores["Intelligence"];};
    int getCharisma(){return abilityScores["Charisma"];};
    int getDexterity(){return abilityScores["Dexterity"];};
    int getStrength() {return abilityScores["Strength"];};


    int getDamageBonus() { return damageBonus; };
    int getArmorClass() { return armorClass; };
    int getHitPoints()  {return hitPoints;};


    ItemContainer* getEquipment() { return equipment; };


    int getHitpoints() const { return hitPoints; };
    int getLevel() const { return level; };
    ItemContainer* getItemContainer() { return equipment;};
    string getName() const { return name; };

    // Accessor method to get the weapon
    Weapon* getWeapon() const {
        auto it = wornEquipment.find("Weapon");
        if (it != wornEquipment.end()) {
            return dynamic_cast<Weapon*>(it->second);  // Return the weapon if found
        }
        return nullptr;  // Return nullptr if no weapon is equipped
    }

    map<string,Item*> getWornEquipment() const {
        return wornEquipment;
    }
    // setter methods
    void setHitpoints(int hp) {  hitPoints = hp; Notify();};
    void setArmorClass(int ac) {  armorClass = ac; Notify();};
    void setDamageBonus(int db) {  damageBonus = db; Notify();};

    void setItemContainer(ItemContainer *itemContainer) {itemContainer = itemContainer;};

    void setAbilityScores(const string& ability,int score){abilityScores[ability] = score;}


    /**
    * @brief method to set the Character's level.
    *
    * Implementations should call CalculateAttributes, to update Hitpoints, and Bonuses
    */
    void adjustLevel(int level);


    /**
    * @brief Pure virtual method to calculate derived attributes.
    *
    * Implementations should calculate attributes specific to the character type, such as attack bonuses and hit points, based on the character's level and ability scores.
    */
    virtual void calculateAttributes() = 0;



    /**
    * @brief Simulates rolling dice to generate random numbers.
    *
    * @param numberOfDice The number of dice to roll.
    * @param diceSides The number of sides on each die.
    * @return The total result of the dice rolls.
    */
    static int rollDice(int numberOfDice, int diceSides);

    /**
    * @brief Pure virtual method to display the character's attribute sheet.
    *
    * Implementations should output all relevant character information, including name, level, ability scores, derived attributes, and equipped Items.
    */
    virtual void displayCharacterSheet() const;


    /**
     * @brief Adds Item to the Item Container
     *
     * @param item
     * @return
     */
    bool equip(Item *item);

    /**
     * @brief Removes the Item from the Container
     *
     * @param item
     * @return
     */
    bool unequip(int index);

    /**
     * @brief wears and Item from the container
     *
     * @param index
     * @return
     */
    bool wearItem(int index);

    /**
     * @brief remove the worn Item and add it to the container
     *
     * @return
     */
    bool remove(string type);

    /**
     * @brief Level Up a character by One
     *
     * @param void
     * @return Confirmation whether the Level is increased or not
     */
    virtual bool levelUp() = 0;

    bool attack(Character* target, int attackRoll);

    void onAttacked();
protected:
    string name;
    int level;

    map<string, int> abilityScores; // Basic Attributes
    map<string, int> modifiers;
    vector<int> attackBonus;
    int armorClass, damageBonus; // Derived Attributes
    map<string,Item*> wornEquipment;
    ItemContainer* equipment; // Equipment

    /**
    * @brief Generates random ability scores for the character.
    *
    * This method populates the abilityScores map with randomly generated values for each ability score, simulating the rolling of dice.
    */
    void generateAbilityScores();

    /**
    * @brief Calculates the modifier for an ability score.
    *
    * @param abilityScore The ability score from which to calculate the modifier.
    * @return The calculated modifier, based on the ability score.
    */
    static int calculateModifier(int abilityScore);

    /**
    * @brief Pure virtual method to calculate the character's hit points.
    *
    * Implementations should determine the character's total hit points based on level, class, and Constitution modifier.
    */
    virtual void calculateHitPoints() = 0;

    /**
    * @brief Pure virtual method to calculate the character's armor class.
    *
    * Implementations should calculate the armor class based on equipped armor, Dexterity modifier, and any class-specific bonuses.
    */
    virtual void calculateArmorClass() = 0;


    /**
    * @brief Pure virtual method to calculate the character's damage bonus.
    *
    * Implementations should calculate the damage bonus based on the character's Strength modifier and any class-specific bonuses.
    */
    virtual void calculateDamageBonus() = 0;

    /**
    * @brief Retrieves the armor class value of a specified armor.
    *
    * @param armorName The name of the armor whose AC value is to be retrieved.
    * @return The armor class (AC) value of the specified armor.
    */
    static int getArmorACValue(const string& armorName);

    friend std::ostream& operator<<(std::ostream& os, const Character& character);

    friend std::istream& operator>>(std::istream& is, Character& character);

private:
    /**
     * @brief Rolls Dice according to game rules
     *
     * @return Score calculated
     */
    int generateScore();

    /**
     * @brief Updates Bonus when new character is made
     *
     * @return void
     */
    void UpdateAttackBonus();

    std::list<IObserver*> observers;

};

