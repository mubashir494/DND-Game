//
// Created by Roger Sioufi on 2024-02-18.
//

#ifndef COMP345A1_RING_H
#define COMP345A1_RING_H

#include "../Item/Item.h"
#include <vector>
#include <stdexcept> // For std::runtime_error
#include <algorithm> // For std::find

/**
 * @class Ring
 * @brief Represents a ring item
 *
 * Game Rules: Ring may enhance Armor Class, Constitution, Strength, Wisdom, or Charisma.
 * Design: Inherits from Item and specifies Ring-related functionality.
 * Libraries: Inherits <string> from Item.h.
 */
class Ring: public Item {
public:
    /**
     * @brief Construct a new Ring object.
     *
     * @param name The name of the ring.
     * @param enchantment The enchantment applied to the ring.
     */
    Ring(const std::string& name);
    
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

    /**
* Serialization operator for
* @param os
* @param itemContainer
* @return
*/
    friend std::ostream& operator<<(std::ostream& os, const Ring& Item);

    /**
     *  Deserialization operator for Item.
     * @param is
     * @param ItemContainer
     * @return
     */
    friend std::istream& operator>>(std::istream& is, Ring& item);
};


#endif //COMP345A1_RING_H
