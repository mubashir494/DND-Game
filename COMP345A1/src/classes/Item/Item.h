//
// Created by Roger Sioufi on 2024-02-18.
//

#ifndef COMP345A1_ITEM_H
#define COMP345A1_ITEM_H

#include <string>
#include <stdexcept>
#include <map>
#include <iostream>
#include "../Dice/Dice.h"

using namespace std;

/**
* @brief Enum class for the different types of enchantments
*
* Game Rules: Enchantments can be of different types and have different bonuses.
*/
/**
 * @brief Base class for all item types in the game
 *
 * Game Rules: Items can influence character stats and have enchantments.
 * Design: Serves as a base for derived item classes like Helmet, Armor, etc.
 * Libraries: <string> for item names
 *
 */
class Item {
protected:
    string name;
    map<string, int> abilityScores; // Basic Attributes
    bool equipped;
    int hitPoints, armorClass, damageBonus, attackBonus; // Derived Attributes

public:
    /**
    * @brief Construct a new Item object.
    *
    * @param name The name of the item.
    * @param enchantment The enchantment applied to the item.
    */
    Item(const string& name);

    /**
    * @brief Destructor for the Item object.
    *
    */
    virtual ~Item();



    /**
    * @brief Get the type of the item.
    *
    * @return string Returns the type of the item.
    */
    virtual string getType() const = 0;

    /**
     * @brief Function to return the name of the item.
     * @return string Returns name of the item.
     */
    string getName() const;



    /**
     * @brief Will set Attributes for each type of Weapon
     *
     */
    void virtual CalculateAttributes() = 0 ;

    /**
     * Custom Roll for the item ability
     *
     * @return
     */
     int rollDice();

     /**
      * @brief print weapon on the console
      *
      */
      void printWeapon();

      /**
       * @brief gets armor class
       *
       * @return
       */
      int getArmorClass(){return armorClass;};

      /**
       * @brief getter and setters for equipped
       */
       bool getEquipped() {return equipped;};

       /**
        * @brief set Equipped
        */
        void setEquipped(bool value){equipped = value; };

        void setAttackBonus(int atk) {attackBonus = atk;};
    void setHitpoints(int hp) {  hitPoints = hp;};
    void setArmorClass(int ac) {  armorClass = ac;};
    void setDamageBonus(int db) {  damageBonus = db;};

    void setAbilityScores(const string& ability,int score){abilityScores[ability] = score;}

    map<string, int> getAbilityScores() {return abilityScores;};

    int getAttackBonus(){return attackBonus;};

    int getDamageBonus(){return damageBonus;};

    /**
    * Serialization operator for
    * @param os
    * @param itemContainer
    * @return
    */
    friend std::ostream& operator<<(std::ostream& os, const Item& Item);

    /**
     *  Deserialization operator for Item.
     * @param is
     * @param ItemContainer
     * @return
     */
    friend std::istream& operator>>(std::istream& is, Item& item);

private:
    /**
     * @brief Initializes attributes
     *
     *
     */
    void initializeAttributes();



};


#endif //COMP345A1_ITEM_H
