//
// Created by Roger Sioufi on 2024-02-18.
//

#ifndef COMP345A1_WEAPON_H
#define COMP345A1_WEAPON_H

#include "../Item/Item.h"
#include <vector>
#include <stdexcept> // For std::runtime_error
#include <algorithm> // For std::find

/**
 * @class Weapon
 * @brief Represents a weapon item
 *
 * Game Rules: Weapon may enhance Attack Bonus or Damage bonus.
 * Design: Inherits from Item and specifies Weapon-related functionality.
 * Libraries: Inherits <string> from Item.h.
 */
class Weapon : public Item{

public:
    /**
     * Types of Weapon
     */
     enum WeaponType {
        BOW,
        SWORD
    };
    /**
     *
     */
     WeaponType getWeaponType();
    /**
     * @brief Construct a new Weapon object.
     *
     * @param name The name of the weapon.
     * @param enchantment The enchantment applied to the weapon.
     */
    Weapon(const std::string& name,const WeaponType& weaponType);
    
    /**
     * @brief Get the type of the item.
     *
     * @return std::string Returns the type of the item as a string.
     */
    string getType() const override;

    /**
    * Calculates attribute
    *
    */
    void CalculateAttributes() override;
private:
    WeaponType weaponType;
};


#endif //COMP345A1_WEAPON_H
