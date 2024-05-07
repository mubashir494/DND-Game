//
// Created by hp on 30/03/2024.
//

#include <fstream>
#include "CharacterEditor.h"



Character* CharacterEditor::runCharacterEditor() {
    Character *character;
    int input;
    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1: Create new Player Character" << endl;
        cout << "2: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                character = createCharacter();
                break;
            }
            case 2: {
                return nullptr;
            }
        }
        if(character == nullptr){
            continue;
        }
        else {
            break;
        }
    }
    return character;
}
/**
 * Initially Character are created with level One with no Wepons
 */
Character* CharacterEditor::createCharacter() {

    Character* character;
    string name ;
    int level = 1;
    int typeOfCharacter;
    // get the name of the character from the User

    cout << "Enter the name of your character :";
    cin >> name;
    //getline(cin, name);


    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(true){
        cout << "\nWhat type of fighter do you want to be?" << endl;
        cout << "1: Nimble: known for their agility, speed, and precision" << endl;
        cout << "2: Bully: specialize in direct confrontations and intimidation" << endl;
        cout << "3: Tank: designed to absorb damage" << endl;
        cout << "4: Quit" << endl;
        cout << "Enter option: ";
        cin >> typeOfCharacter;
        cout << endl;

        switch (typeOfCharacter) {
            case 1: {
                NimbleBuilder *builder = new  NimbleBuilder();
                builder->createFighter(name,level);
                character = builder->getFighter();
                break;
            }
            case 2:{
                BullyBuilder *bullyBuilder = new BullyBuilder();
                bullyBuilder->createFighter(name,level);
                character = bullyBuilder->getFighter();
                break;
            }
            case 3: {
                TankBuilder *tankBuilder = new TankBuilder();
                tankBuilder->createFighter(name,level);
                character = tankBuilder->getFighter();
                break;
            }
            case 4:{
                return nullptr;
            }
        }
        if(character != nullptr){
            HumanPlayerStrategy *humanPlayerStrategy = new HumanPlayerStrategy();
            character->setStrategy(humanPlayerStrategy);
            int difficulty;
            while(true) {
                cout << "What difficulty would you like the game to be?" << endl;
                cout << "1: Easy" << endl;
                cout << "2: Medium" << endl;
                cout << "3: Hard" << endl;
                cout << "Enter option: ";
                cin >> difficulty;
                cout << endl;

                switch (difficulty) {
                    case 1: {
                        character->setHitpoints(100);
                        break;
                    }
                    case 2:{
                        character->setHitpoints(50);
                        break;
                    }
                    case 3: {
                        character->setHitpoints(20);
                        break;
                    }
                    default:{
                        cout << "Invalid option. Please try again.\n" << endl;
                        continue;
                    }
                }
                return character;
            }
        }
    }
}



/**
 * NPC RELATED CODE
 *
 */
Character* CharacterEditor::runNpcEditor() {
    int input;
    Character* character;
    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1: Create new NPC" << endl;
        cout << "2: Load from a file" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter option: ";
        cin >> input ;

        switch (input) {
            case 1: {
                character = createNpc();
                break;
            }
            case 2 : {
                character = loadNpc();
                break;
            }
            case 3: {
                return nullptr;
            }
        }
        if(character == nullptr){
            continue;
        }
        else {
            return character;
        }
    }
}

Character* CharacterEditor::loadNpc() {
    Character* character = nullptr;
    string filename;
    cout << "Enter filename to load the map (without the file extension): ";
    cin >> filename;

    filename += ".txt"; // Append .txt extension

    ifstream file(filename);
    if (file.is_open()) {
        character = new Fighter("defaultName",1);

        // Dynamically allocate memory for map and deserialize the map from the file
        file >> *character;

        cout << "Character loaded from file: " << filename << endl;

        character->displayCharacterSheet();

        return character;
    } else {
        cout << "Error: Unable to open file." << endl;
        return character;
    }
}



Character* CharacterEditor::createNpc() {
    Character *character;
    string name ;
    int typeOfNPC;
    int level = 1;
    int typeOfCharacter;
    // get the name of the character from the User
    cout << "Enter the Name of the New Character :";

    cin >>name;

    while(true){
        // Loop for level
        while(true){
            cout << "What is the level of the NPC " << endl;
            cin >> level;
            if(level > 0 && level <= 5){
                break;
            }
        }
        // loop to create different strategies
        while(true){
            cout << "What type of NPC do you want to Create " << endl;
            cout << "1: Aggressor" << endl;
            cout << "2: Friendly" << endl;
            cin >> typeOfNPC;
            if(typeOfNPC == 1 || typeOfNPC == 2){
                break;
            }
        }

        cout << "What Type of Fighter You want to Make" << endl;
        cout << "\nChoose an option:" << endl;
        cout << "1: Nimble" << endl;
        cout << "2: Bully" << endl;
        cout << "3: Tank" << endl;
        cout << "4: Quit" << endl;
        cout << "Enter option: ";
        cin >> typeOfCharacter;

        switch (typeOfCharacter) {
            case 1: {
                NimbleBuilder *builder = new  NimbleBuilder();
                builder->createFighter(name,level);
                character = builder->getFighter();
                break;
            }
            case 2:{
                BullyBuilder *bullyBuilder = new BullyBuilder();
                bullyBuilder->createFighter(name,level);
                character = bullyBuilder->getFighter();
                break;
            }
            case 3: {
                TankBuilder *tankBuilder = new TankBuilder();
                tankBuilder->createFighter(name,level);
                character = tankBuilder->getFighter();
                break;
            }
            case 4:{
                return nullptr;
            }
        }


        // For Ability Menu
        while(true){
            int input ;
            cout << "Do you want to EDIT Ability Scores of NPC : Input 1 to Edit" << endl;
            cin >> input;
            if(input == 1){
                abilityMenu(character);
                break;
            }
            break;
        }



        while(true) {
            int input;
            cout << "Do you want to Equip NPC  : Input 1 to Equip" << endl;
            cin >> input;

            if(input == 1){
                ItemContainerEditor itemContainerEditor;
                itemContainerEditor.run(character->getItemContainer());
                break;
            }
            break;
        }

        character->displayCharacterSheet();

        while (true){
           int input;
           cout << "Input the index of the Item You want to Wear : Input -1 to Exit";
           cin >> input;
           if(input == -1 ){
               break;
           }
           character->wearItem(input - 1);
        }




        if(character != nullptr && (typeOfNPC == 1 || typeOfNPC == 2)){

            if(typeOfNPC == 1){
                AggressorStrategy *aggressorStrategy = new AggressorStrategy();
                character->setStrategy(aggressorStrategy);
            }
            else {
                FriendlyStrategy *friendlyStrategy = new FriendlyStrategy();
                character->setStrategy(friendlyStrategy);
            }

            // Prompt user to save the character
            int input;
            cout << "Do you want to Save Character : Input 1 to save Character" << endl;
            cin >> input;
            if(input == 1 ){
                saveNPC(character);
            }
            return character;
        }

    }
}

void CharacterEditor::abilityMenu(Character *pCharacter) {
    int input;
    while(true){
        cout << "What Scores do you want Edit for the NPC (Value cannot be greater then 5)" << endl;
        cout << "\nChoose an option:" << endl;
        cout << "1: Strength" << endl;
        cout << "2: Dexterity" << endl;
        cout << "3: Constitution" << endl;
        cout << "4: Intelligence" << endl;
        cout << "5: Wisdom" << endl;
        cout << "6: Intelligence" << endl;
        cout << "7 :Damage Bonus" << endl;
        cout << "8 :Hit Points" << endl;
        cout << "9 :Armor" << endl;
        cout << "10 :Quit" << endl;
        cin >>input;

        switch (input) {
            case 1 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Strength",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 2 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Dexterity",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 3 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Wisdom",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 4 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Intelligence",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;

            }
            case 5 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Wisdom",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 6 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setAbilityScores("Intelligence",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }

            case 7 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setDamageBonus(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 8 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setHitpoints(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 9 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    pCharacter->setArmorClass(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 10 : {
                return;
            }
        }
    }
}

bool CharacterEditor::saveNPC(Character *pCharacter) {
    string filename;
    cout << "Enter filename to save the NPC: ";
    cin >> filename;

    filename += ".txt"; // Append .txt extension
    ofstream file(filename);
    if (file.is_open()) {
        file << *pCharacter << " "; // Dereference the map pointer to access the Map object and serialize it
        cout << "Character saved to file: " << filename << endl;
        return true;
    } else {
        cout << "Error: Unable to open file." << endl;
        return false;
    }
}



void CharacterEditor::updateWornItemEditor(Character *pCharacter) {
    cout << "------------- Equipped Items: --------------" << endl;
    map<string,Item*> wornEquipment = pCharacter->getWornEquipment() ;
    for (const auto& equipments : wornEquipment) {
        if(equipments.second != nullptr){
            equipments.second->printWeapon();
            cout << "\t\t---------------------------" << endl;
        }
    }
    // print the available equipment
    cout << "------------- Items Inventory: --------------" << endl;
    pCharacter->getEquipment()->printContainer();

    int input;
    while(true){
        cout << "What Action you want to Perform" << endl;
        cout << "1: Equip Item" << endl;
        cout << "2: Remove Item" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter Option: ";

        cin >> input;
        switch (input){
            case 1 : {
                // Logic for wearing items
                while(true) {
                    int index;
                    cout << "\nInput the Index which you want to Wear ? -1 to Quit" << endl;
                    cin >> index;
                    index = index - 1;
                    if(index == -2 ){
                        break;
                    }
                    bool worn = pCharacter->wearItem(index);
                    if(worn){
                        break;
                    }
                }
                cout << "------------- Equipped Items: --------------" << endl;
                map<string,Item*> wornEquipment = pCharacter->getWornEquipment() ;
                for (const auto& equipments : wornEquipment) {
                    if(equipments.second != nullptr){
                        equipments.second->printWeapon();
                        cout << "\t\t---------------------------" << endl;
                    }
                }
                // print the available equipment
                cout << "------------- Items Inventory: --------------" << endl;
                pCharacter->getEquipment()->printContainer();
                break;
            }
            case 2 : {
                removeItem(pCharacter);
                cout << "------------- Equipped Items: --------------" << endl;
                map<string,Item*> wornEquipment = pCharacter->getWornEquipment() ;
                for (const auto& equipments : wornEquipment) {
                    if(equipments.second != nullptr){
                        equipments.second->printWeapon();
                        cout << "\t\t---------------------------" << endl;
                    }
                }
                // print the available equipment
                cout << "------------- Items Inventory: --------------" << endl;
                pCharacter->getEquipment()->printContainer();
                break;
                // Login removing items
            }
            case 3 : {
                return;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                continue;
            }
        }


    }

}

void CharacterEditor::removeItem(Character* pCharacter) {

    while(true) {
        int index;
        cout << "Which type of item do you want to remove ? -1 to Quit" << endl;
        cout << "1: Armor" << endl;
        cout << "2: Belt" << endl;
        cout << "3: Boots" << endl;
        cout << "4: Helmet" << endl;
        cout << "5: Ring" << endl;
        cout << "6: Shield" << endl;
        cout << "7: Weapon" << endl;
        cout << "8: Quit" << endl;
        cout << "\nEnter Option: ";
        cin >> index;
        cout << endl;

        switch (index) {
            case 1 : {
                pCharacter->remove("Armor");
                break;

            }
            case 2 : {
                pCharacter->remove("Belt");
                break;
            }
            case 3 :{
                pCharacter->remove("Boots");
                break;
            }
            case 4 : {
                pCharacter->remove("Helmet");
                break;
            }
            case 5 : {
                pCharacter->remove("Ring");
                break;
            }
            case 6 : {
                pCharacter->remove("Shield");
                break;

            }
            case 7 : {
                pCharacter->remove("Weapons");
                break;
            }
            case 8 : {
                return;
            }
            default:{
                cout << "Invalid option. Please try again." << endl;
                continue;
            }
        }
    }

}


