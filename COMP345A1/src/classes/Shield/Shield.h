//
// Created by Roger Sioufi on 2024-02-18.
//

#ifndef COMP345A1_SHIELD_H
#define COMP345A1_SHIELD_H

#include "../Item/Item.h"
#include <vector>
#include <stdexcept> // For std::runtime_error
#include <algorithm> // For std::find

/**
 * @class Shield
 * @brief Represents a shield item
 *
 * Game Rules: Shield may enhance Armor Class.
 * Design: Inherits from Item and specifies Shield-related functionality.
 * Libraries: Inherits <string> from Item.h.
 */
class Shield: public Item {

public:
    /**
     * @brief Construct a new Shield object.
     *
     * @param name The name of the shield.
     * @param enchantment The enchantment applied to the shield.
     */
    Shield(const std::string& name);
    
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
};


#endif //COMP345A1_SHIELD_H
