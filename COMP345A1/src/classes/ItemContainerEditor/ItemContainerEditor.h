//
// Created by hp on 30/03/2024.
//

#ifndef COMP345A1_ITEMCONTAINEREDITOR_H
#define COMP345A1_ITEMCONTAINEREDITOR_H

#include "../ItemContainer/ItemContainer.h"
#include "../Item/Item.h"

class ItemContainer;
class Item;
class ItemContainerEditor {
public:
    ItemContainerEditor() = default;
    ItemContainer* run(ItemContainer *container);
private:
    void weaponSelector(ItemContainer* container);
    void abilityMenu(Item *item);

};


#endif //COMP345A1_ITEMCONTAINEREDITOR_H
