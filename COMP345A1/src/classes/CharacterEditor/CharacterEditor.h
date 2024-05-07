//
// Created by hp on 30/03/2024.
//



#ifndef COMP345A1_CHARACTEREDITOR_H
#define COMP345A1_CHARACTEREDITOR_H

#include "../Character/Character.h"
#include "../Builder/NimbleBuilder.h"
#include "../Builder/BullyBuilder.h"
#include "../Builder/TankBuilder.h"
#include "../ItemContainerEditor/ItemContainerEditor.h"


class CharacterEditor {

public:
    CharacterEditor() = default;
    Character* runNpcEditor();
    Character* runCharacterEditor();
    Character* loadNpc();
    Character* createNpc();
    Character* createCharacter();
    bool saveNPC(Character *pCharacter);
    void updateWornItemEditor(Character* pCharacter);
private:
    void abilityMenu(Character *pCharacter);
    void removeItem(Character* pCharacter);


    // Pointer to character which we are currently editing
//    Character* character;

};


#endif //COMP345A1_CHARACTEREDITOR_H
