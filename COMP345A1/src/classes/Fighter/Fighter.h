#pragma once
#include "../Character/Character.h"
#include "../Dice/Dice.h"
#include "../Item/Item.h"

/**
 * @file Fighter.h
 * @brief Fighter class extending the Character with specialized combat abilities.
 *
 * This file defines the Fighter class, which inherits from Character to provide
 * specific implementations for a combat-oriented character type in the Basic Fantasy RPG setting.
 * It includes overrides for attribute calculations to reflect the fighter's combat proficiency.
 *
 * Game Rules Involved:
 * - Fighters receive bonuses to attack and damage, reflecting their training in combat.
 * - The class implements specialized calculations for hit points, armor class, attack bonus,
 *   and damage bonus to adhere to the Basic Fantasy RPG rules that enhance a fighter's
 *   effectiveness in battle.
 *
 * Design Brief:
 * - Inherits from Character to utilize common character functionalities while providing
 *   specific implementations for calculateAttributes, calculateHitPoints, calculateArmorClass,
 *   calculateAttackBonus, and calculateDamageBonus methods to tailor the fighter's capabilities.
 * - This design follows the principle of specialization, allowing the Fighter class to modify
 *   and extend base class behaviors to fit the fighter archetype's unique characteristics.
 *
 * Libraries Used:
 * - Inherits "Character.h" for base character functionalities. The decision to inherit from
 *   Character allows for code reuse and adherence to object-oriented principles, promoting
 *   consistency and maintainability across different character types within the game.
 */

class Fighter : public Character {
public:

    /**
    * @brief Constructs a Fighter character with a name and level.
    *
    * @param name The name of the fighter.
    * @param level The initial level of the fighter.
    */
    Fighter(const string& name, int level);

    /**
     * @brief Destructor for the Fighter class.
     */
    ~Fighter() override = default;

    /**
    * @brief Calculates derived attributes specific to the Fighter class.
    *
    * This includes adjustments to hit points, armor class, attack bonus, and damage bonus to reflect
    * the fighter's combat proficiency.
    */
    void calculateAttributes() override;

    /**
    * @brief Calculates and sets the hit points for the Fighter.
    *
    * Overrides the base class method to provide a higher base hit point total, emphasizing the fighter's
    * robustness in combat.
    */
    void calculateHitPoints() override;

    /**
    * @brief Calculates and sets the armor class (AC) for the Fighter.
    *
    * Takes into account the fighter's ability to use heavier armors effectively, potentially leading to
    * a higher AC than other character classes.
    */
    void calculateArmorClass() override;

    /**
    * @brief Calculates and sets the damage bonus for the Fighter.
    *
    * Reflects the fighter's ability to inflict more damage in combat due to their strength and mastery of weapons.
    */
    void calculateDamageBonus() override;

    /**
    * @brief Displays the Fighter's character sheet.
    *
    * Outputs all relevant information about the fighter, including their enhanced combat statistics.
    */
    void displayCharacterSheet() const override;

    /**
     * Override Level Up function in character
     *
     * @return
     */
    virtual bool levelUp() override;
};


