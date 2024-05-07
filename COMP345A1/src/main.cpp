#include <iostream>
#include <fstream>
#include "classes/Fighter/Fighter.h"
#include "classes/Map/Map.h"
#include "classes/Dice/Dice.h"
#include "classes/Helmet/Helmet.h"
#include "classes/CharacterStrategy/CharacterStrategy.h"
#include "classes/GameLogger/GameLogger.h"
#include "classes/Shield/Shield.h"
#include "classes/ItemContainer/ItemContainer.h"
#include "classes/Ring/Ring.h"
#include "classes/ObserverPattern/CharacterObserver.h"
#include "classes/MapBuilders/MapEditorBuilder.h"
#include "classes/MapBuilders/GameLevelMapBuilder.h"
#include "classes/MapEditor/MapEditor.h"
#include "classes/CharacterEditor/CharacterEditor.h"
#include "classes/ItemContainerEditor/ItemContainerEditor.h"
#include "classes/Armor/Armor.h"
#include "classes/Game/Game.h"
#include "classes/Weapon/Weapon.h"


//void displayCharacter();
//void displayStrategy();
//void displayMapBuilder();
//void characterObserver();
//void displayMap();
//void displayMapEditor();
//void displayItemContainer();
//void displayDice();
//void displayMapBuilder();
//void displayGameLevelMapBuilder();
//void displayMapEditor();
//void displayCharacterBuilder();
//void displayFileContent(const std::string& filePath);
//void displayCharacterEditor();
//void  displayChestEditor();
//void displayNpcEditor();

int main() {

    Game * game = new Game();
    game->play();

//    displayCharacter();
//    displayFileContent("../src/map_example.txt");
//    displayMap();
//    displayMapBuilder();
//    displayGameLevelMapBuilder();
//    displayMapEditor();
//    displayItemContainer();
//    displayDice();
//    displayCharacterBuilder();
//    displayCharacterEditor();
//    displayChestEditor();
//    displayStrategy();

    /*auto *p1 = new Fighter("Player1",4);
    p1->getAbilityScores();

    auto *npc = new Fighter("NPC",4);
    npc->getAbilityScores();

    Map* map1 = new Map(10,5);

    auto* log = new GameLogger();
    map1->attach(log);
    p1->attach(log);

    map1->placeOpponent(npc, 8, 2);

    auto* campaign = new Campaign(10,10);

    campaign->maps[0]->Place(1,2,'#');
    campaign->maps[0]->Place(2,2,'#');
    campaign->maps[0]->Place(0,3,'S');
    campaign->maps[0]->Place(0,1,'E');

    auto* humanStrategy = new HumanPlayerStrategy();
    p1->setStrategy(humanStrategy);
    campaign->maps[0]->placeCharacter(p1);

    auto* agressorStrategy = new AggressorStrategy();
    npc->setStrategy(agressorStrategy);
    campaign->maps[0]->placeOpponent(npc, 8, 2);

    campaign->addMap(map1);

    campaign->maps[1]->Place(1,2,'#');
    campaign->maps[1]->Place(2,2,'#');
    campaign->maps[1]->Place(0,3,'S');
    campaign->maps[1]->Place(0,1,'E');

    // Player1's turn (Human Strategy)
    campaign->maps[0]->printMap();
    p1->move(campaign->maps[0]);
    p1->attack(campaign->maps[0]);

    // NPC's turn (Agressor Strategy)
    npc->move(campaign->maps[0]);
    npc->attack(campaign->maps[0]);

    // Player1's turn (Human Strategy)
    p1->move(campaign->maps[0]);
    p1->attack(campaign->maps[0]);

    // NPC's turn (Agressor Strategy)
    npc->move(campaign->maps[0]);
    npc->attack(campaign->maps[0]);

    // Player1's turn (Human Strategy)
    p1->move(campaign->maps[0]);
    p1->attack(campaign->maps[0]);*/

    return 0;
}

void displayDice() {
    Dice dice;
    string diceInput;
    cout << "Enter a string of the form xdy[+z], where:\n"
            "\tx is the number of dice,\n"
            "\tdy the kind of dice (d4, d6, d8, d10, d12, d20 or d100),\n"
            "\tz is a negative of positive number added after all the dice results have been added (optional).\n"
            "\nDice Input: ";
    cin >> diceInput;
    try {
        int diceResult = dice.roll(diceInput);
        cout << "\tRolled: " << diceInput << ", Result: " << diceResult << endl;
        cout << "\nMore Dice Roll Examples:"<< endl;
        cout << "\tRolled: " << "55d100-26" << ", Result: " << dice.roll("55d100-26") << endl;
        cout << "\tRolled: " << "3d20" << ", Result: " << dice.roll("3d20") << endl;
        cout << "\tRolled: " << "3d8-0" << ", Result: " << dice.roll("3d8-0") << endl;
        cout << "\tRolled: " << "3d4+15" << ", Result: " << dice.roll("3d4+15") << endl;
        cout << "\tRolled: " << "9d20+1" << ", Result: " << dice.roll("9d20+1") << endl;
        cout << "\tRolled: " << "7d6" << ", Result: " << dice.roll("7d6") << endl;
        cout << "\tRolled: " << "1d6-100" << ", Result: " << dice.roll("1d6-100") << endl;
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

}

void displayFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for comparison: " << filePath << std::endl;
        return;
    }

    std::cout << "Original map content from file:\n";
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
    file.close();
}


void displayMapBuilder() {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Display Map Builder: Part 4.1" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    MapEditorBuilder builder;
    std::string filePath = "../src/map_example.txt";
    std::cout << "Building the Map from: " <<filePath << std::endl;

    builder.loadMap(filePath);
    Map* loadedMap = builder.getMap();

    if (loadedMap != nullptr) {
        std::cout << "Map loaded successfully.\n";
        loadedMap->printMap(); // This will print the map to the console
    } else {
        std::cerr << "Failed to load map.\n";
    }
    displayFileContent(filePath);

}

void displayCharacter(){
    Fighter f1("test1", 5);

    cout << "\nShowing that the initialization of the two fighter is generated randomly. \n\n";
    Fighter f2("test2", 10);

    Item* shield = new Shield("Defender's Shield");
    Item* ring = new Ring("Ring of Strength");

    f1.levelUp();
    f1.levelUp();
    f1.equip(shield);
    f1.equip(ring);
    f1.wearItem(0);
    f1.wearItem(0);
//    f1.remove();

    f1.displayCharacterSheet();
    f2.displayCharacterSheet();

    // Demonstrate utility function usage
    int diceRoll = Character::rollDice(1, 20); // Simulating a d20 roll
    std::cout << "\nSimulating a d20 roll: " << diceRoll << std::endl;
};

void characterObserver(){
    Fighter* fighter = new Fighter("fighter 1", 10);
    CharacterObserver* characterObserver = new CharacterObserver(fighter);

    cout << "calling the display method of the character to show initial state \n\n";
    fighter->displayCharacterSheet();

    cout << "\ncharacter sheet updated following a change to hitPoints \n\n";
    fighter->setHitpoints(20);

    cout << "\n";

}

void displayStrategy(){
    auto *p1 = new Fighter("Player1",4);
    auto *npc = new Fighter("NPC",4);
    p1->getAbilityScores();
    npc->getAbilityScores();

    // Create a Map and a Dice
    Map* map = new Map(10,5);
    Dice* dice = new Dice();

    //Create a Game Logger
    auto* log = new GameLogger();
    dice->attach(log);
    map->attach(log);
    p1->attach(log);
    npc->attach(log);

    // Design the Map
    map->Place(1,2,'#');
    map->Place(2,2,'#');
    map->Place(0,3,'S');
    map->Place(0,1,'E');

    // Check if the Map is valid or not
    map->isValid();

    // Start Game for the fighters
    map->placeCharacter(p1);
    map->placeNPC(npc, 8, 2);
    map->printMap();

    // Player1's turn (Human Strategy)
    auto* humanStrategy = new HumanPlayerStrategy();
    p1->setStrategy(humanStrategy);
    p1->move(map);
    p1->attack(map);
    p1->freeAction(map);

    // NPC's turn (Friendly Strategy)
    auto* friendlyStrategy = new FriendlyStrategy();
    npc->setStrategy(friendlyStrategy);
    npc->move(map);
    npc->attack(map);

    // Player1's turn (Human Strategy)
    p1->move(map);
    p1->attack(map);
    p1->freeAction(map);

    // NPC's turn (Aggressor Strategy)
    npc->move(map);
    npc->attack(map);

    // switch on/off logging sources
    npc->setLogging(false);

}

void displayGameLevelMapBuilder() {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Display Map Builder with Level Adjustments: Part 4.2" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    GameLevelMapBuilder builder;
    std::string filePath = "../src/map_example.txt";

    builder.loadMap(filePath);
    Map* loadedMap = builder.getMap();

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Displaying the Fighter sheet before entering the game:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    Fighter *f1 = new Fighter("teemo",4);
    loadedMap->placeCharacter(f1);
    f1->displayCharacterSheet();

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Building the Map from: " <<filePath << std::endl;
    std::cout << "---------------------------------" << std::endl;

    if (loadedMap != nullptr) {
        std::cout << "Map loaded successfully.\n";
        loadedMap->printMap(); // This will print the map to the console
    } else {
        std::cerr << "Failed to load map.\n";
    }
    displayFileContent(filePath);

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Displaying the Fighter sheet after entering the game with level 15:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    builder.adaptToLevel(15);
    f1->displayCharacterSheet();
}

void displayMapEditor() {
    Game game;
    game.play();
//    Character *f1 = new Fighter("abc",4);
//    Character *f2 = new Fighter("cde",4);
//    Item* w1 = new Armor("armor");
//    Item* w2 = new Weapon("armorhello",Weapon::WeaponType::BOW);
//    f1->equip(w1);
//    f1->equip(w2);
//    cout << *f1;
//    cin >> *f2;
//    f2->displayCharacterSheet();
//
//    ItemContainer *itemContainer = new ItemContainer();
//    itemContainer->addItem(w1);
//    itemContainer->addItem(w2);
//
//    ItemContainer *itemContainer1 = new ItemContainer();
//    cout << *itemContainer;
//    cin >> *itemContainer1;
//
//
//    itemContainer->printContainer();
//
//    itemContainer1->printContainer();

}

void displayCharacterEditor(){
//    std::cout << "\n\n-----------------------------------------------" << std::endl;
//    std::cout << "\tWemcome to the Character Editor" << std::endl;
//    std::cout << "-----------------------------------------------" << std::endl;
//    CharacterEditor characterEditor;
//    characterEditor.runCharacterEditor();
//    Campaign* c1 = new Campaign(5,5);
//    cout << *c1;
//    Campaign* c2 = new Campaign(6,6);
//    cin >> *c2;
//    c2->printCampaign();


}

//void displayChestEditor(){
//    std::cout << "\n\n-----------------------------------------------" << std::endl;
//    std::cout << "\tWemcome to the Chest Editor" << std::endl;
//    std::cout << "-----------------------------------------------" << std::endl;
//
//    ItemContainerEditor itemContainerEditor;
//    itemContainerEditor.run();
//
//}
//
//void displayNpcEditor() {
//    std::cout << "\n\n-----------------------------------------------" << std::endl;
//    std::cout << "\tWemcome to the NPC Editor" << std::endl;
//    std::cout << "-----------------------------------------------" << std::endl;
//
//    CharacterEditor *editor = new CharacterEditor();
//    editor->runNpcEditor();
//};

